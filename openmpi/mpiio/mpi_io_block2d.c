#include "malloc2D.h"
#include "mpi.h"
#include "mpi_io_file_ops.h"
#include "stdlib.h"
#include <stdio.h>

void init_array(int ny, int nx, int ng, double **array) {

  for (int j = 0; j < ny + 2 * ng; j++) {
    for (int i = 0; i < nx + 2 * ng; i++) {
      array[j][i] = 0.0;
    }
  }
}

void fill(int ny, int nx, int ng, double **array) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int icount = 1;
  for (int j = ng; j < ny + ng; j++) {
    for (int i = ng; i < nx + ng; i++) {
      array[j][i] = (double)(icount + 100 * rank);
      icount++;
    }
  }
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  int rank, nprocs;
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &nprocs);

  MPI_Comm mpi_io_comm = MPI_COMM_NULL;
  int nfiles = 1;
  float ranks_per_file = (float)nprocs / (float)nfiles;
  int color = (int)((float)rank / ranks_per_file);
  MPI_Comm_split(MPI_COMM_WORLD, color, rank, &mpi_io_comm);
  int nprocs_color, rank_color;
  MPI_Comm_size(mpi_io_comm, &nprocs_color);
  MPI_Comm_rank(mpi_io_comm, &rank_color);

  int row_color = 1, col_color = rank_color;
  MPI_Comm mpi_row_comm, mpi_col_comm;
  MPI_Comm_split(mpi_io_comm, row_color, rank_color, &mpi_row_comm);
  MPI_Comm_split(mpi_io_comm, col_color, rank_color, &mpi_col_comm);

  /* printf("NPC:%d\tR:%d\tC:%d\tRC:%d\n", nprocs_color, rank, color,
   * rank_color); */

  int ndims = 2, ng = 2, ny = 10, nx = 10;
  int global_subsizes[] = {ny, nx};

  int ny_offset = 0, nx_offset = 0;
  MPI_Exscan(&nx, &nx_offset, 1, MPI_INT, MPI_SUM, mpi_row_comm);
  MPI_Exscan(&ny, &ny_offset, 1, MPI_INT, MPI_SUM, mpi_col_comm);
  int global_offsets[] = {ny_offset, nx_offset};
  /* printf("Rank:%d\t\tny:%d\tnx:%d\tnyo:%d\tnxo:%d\n", rank, ny, nx,
   * ny_offset, */
  /* nx_offset); */

  int ny_global, nx_global;
  MPI_Allreduce(&nx, &nx_global, 1, MPI_INT, MPI_SUM, mpi_row_comm);
  MPI_Allreduce(&ny, &ny_global, 1, MPI_INT, MPI_SUM, mpi_col_comm);
  int global_sizes[] = {ny_global, nx_global};
  int data_size = ny_global * nx_global;

  printf("Rank:%d\tnx:%d\tny:%d\toff_x:%d\toff_y:%d\tgx:%d\tgy:%d\n", rank, nx,
         ny, nx_offset, ny_offset, nx_global, ny_global);

  double **data = (double **)malloc2D(ny + 2 * ng, nx + 2 * ng);
  double **data_restore = (double **)malloc2D(ny + 2 * ng, nx + 2 * ng);
  init_array(ny, nx, ng, data);
  init_array(ny, nx, ng, data_restore);
  fill(ny, nx, ng, data);

  MPI_Datatype memspace = MPI_DATATYPE_NULL;
  MPI_Datatype filespace = MPI_DATATYPE_NULL;
  mpi_io_file_init(ng, ndims, global_sizes, global_subsizes, global_offsets,
                   &memspace, &filespace);

  char filename[30];
  if (nfiles > 1) {
    sprintf(filename, "example_%02d.data", color);
  } else {
    sprintf(filename, "example.data");
  }
  write_mpi_io_file(filename, data, data_size, memspace, filespace,
                    mpi_io_comm);
  // Read back the data for verifying the file operations
  read_mpi_io_file(filename, data_restore, data_size, memspace, filespace,
                   mpi_io_comm);
  mpi_io_file_finalize(&memspace, &filespace);

  if (rank == 0)
    printf("Verifying  checkpoint\n");

  int ierr = 0;
  // verification
  for (int j = 0; j < ny + 2 * ng; j++) {
    for (int i = 0; i < nx + 2 * ng; i++) {
      if (data_restore[j][i] != data[j][i]) {
        ierr++;
        printf("DEBUG -- j %d i %d restored %lf data %lf\n", j, i,
               data_restore[j][i], data[j][i]);
      }
    }
  }
  int ierr_global = 0;
  MPI_Allreduce(&ierr, &ierr_global, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
  if (rank == 0 && ierr_global == 0) {
    printf("   Checkpoint has been verified\n");
  }

  
  if (rank == 0) {
     FILE *fp = fopen("example.data","rb");
     for (int j = 0; j < 10; j++){
       printf("x[%d][ ] ",j);
       for (int i = 0; i < 40; i++){
         double x;
         fread(&x, sizeof(double), 1, fp);
         printf("%3.0lf ",x);
       }   
       printf("\n");
     }   
  }
  free(data);
  free(data_restore);
  MPI_Finalize();
  return 0;
}
