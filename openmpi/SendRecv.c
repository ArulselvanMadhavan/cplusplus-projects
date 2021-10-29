#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  int count = 10;
  double xsend[count], xrecv[count];
  for (int i = 0; i < count; i++) {
    xsend[i] = (double)i;
  }
  int rank, nprocs;
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &nprocs);
  if (nprocs % 2 == 1) {
    if (rank == 0) {
      printf("Error:Need even number of processes");
    }
  }
  int tag = rank / 2;
  int partner_rank = tag * 2 + rank % 2;
  MPI_Request request;

  MPI_Isend(xsend, count, MPI_DOUBLE, partner_rank, tag, comm, &request);
  MPI_Recv(xrecv, count, MPI_DOUBLE, partner_rank, tag, comm,
           MPI_STATUS_IGNORE);
  MPI_Request_free(&request);

  if (rank == 0)
    printf("Done");
  MPI_Finalize();
  return 0;
}
