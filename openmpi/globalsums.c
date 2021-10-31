#include "mpi.h"
#include <stdio.h>
int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  int rank, nprocs;
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &nprocs);
  if(rank==0){
    printf("Total procs %d", nprocs);
  }
  MPI_Finalize();
  return 0;
}

struct esum_type {
  double sum;
  double correction;
};

MPI_Datatype EPSUM_TWO_DOUBLES;
MPI_Op KAHAM_SUM;

void kahan_sum(struct esum_type *in, struct esum_type *inout, int *len, MPI_Datatype *EPSUM_TWO_DOUBLES)
{
  
}

void init_kahan_sum(void)
{
  MPI_Type_contiguous(2, MPI_DOUBLE, &EPSUM_TWO_DOUBLES);
  MPI_Type_commit(&EPSUM_TWO_DOUBLES);
  int commutative = 1;
  MPI_Op_create((MPI_User_function *)kahan_sum,  commutative, &KAHAM_SUM);
}
