#ifndef _MPI_IO_FILE_OPS_H
#define _MPI_IO_FILE_OPS_H
#include "mpi.h"

void mpi_io_file_init(int ng, int ndims, int *global_sizes,
                      int *global_subsizes, int *global_starts,
                      MPI_Datatype *memspace, MPI_Datatype *filespace);

void mpi_io_file_finalize(MPI_Datatype *memspace, MPI_Datatype *filespace);
void write_mpi_io_file(const char *filename, double **data, int data_size,
                       MPI_Datatype memspace, MPI_Datatype filespace, MPI_Comm comm);
void read_mpi_io_file(const char *filename, double **data, int data_size,
		      MPI_Datatype memspace, MPI_Datatype filespace, MPI_Comm comm);
#endif
