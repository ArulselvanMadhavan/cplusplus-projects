#include "mpi.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  double max_time, min_time, avg_time, main_time = 0;
  int rank, nprocs = 0;
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &nprocs);

  MPI_Barrier(comm);
  double start_time = MPI_Wtime();
  sleep(3);
  main_time = MPI_Wtime() - start_time;
  MPI_Reduce(&main_time, &min_time, 1, MPI_DOUBLE, MPI_MIN, 0, comm);
  MPI_Reduce(&main_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, comm);
  MPI_Reduce(&main_time, &avg_time, 1, MPI_DOUBLE, MPI_SUM, 0, comm);
  if (rank == 0) {
    printf("Min:%lf\tMax:%lf\tAvg:%lf\n", min_time, max_time, avg_time/nprocs);
  }
  MPI_Finalize();
  return 0;
}
