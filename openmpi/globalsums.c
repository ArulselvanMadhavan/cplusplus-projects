#include "mpi.h"
#include "timer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ORDERS_OF_MAGNITUDE 1.0e9

struct esum_type {
  double sum;
  double correction;
};

MPI_Datatype EPSUM_TWO_DOUBLES;
MPI_Op KAHAN_SUM;

void kahan_sum(struct esum_type *in, struct esum_type *inout, int *len,
               MPI_Datatype *EPSUM_TWO_DOUBLES) {
  double corrected_next_term, new_sum;
  corrected_next_term = in->sum + (in->correction + inout->correction);
  new_sum = inout->sum + corrected_next_term;
  inout->correction = corrected_next_term - (new_sum - inout->sum);
  inout->sum = new_sum;
}

/* Create custom type and custom operator */
void init_kahan_sum(void) {
  MPI_Type_contiguous(2, MPI_DOUBLE, &EPSUM_TWO_DOUBLES);
  MPI_Type_commit(&EPSUM_TWO_DOUBLES);
  int commutative = 1;
  MPI_Op_create((MPI_User_function *)kahan_sum, commutative, &KAHAN_SUM);
}

const double HIGH_VALUE = 1.0e-1;
const double LOW_VALUE = HIGH_VALUE / ORDERS_OF_MAGNITUDE;

double *init_energy(int rank, int nprocs, long ncells, long *nsize,
                    double *acc_sum, MPI_Comm comm) {
  long cells_per_proc = ncells / nprocs;
  long ibegin = rank * cells_per_proc;
  long iend = (rank + 1) * cells_per_proc;
  long nsize_out = iend - ibegin;

  double *local_energy = (double *)malloc(nsize_out * sizeof(double));
  long ncellsdiv2 = ncells / 2;
  *acc_sum = (HIGH_VALUE * ncellsdiv2) + (LOW_VALUE * ncellsdiv2);
  for (long i = 0; i < nsize_out; i++) {
    long cell_id = ibegin + i;
    local_energy[i] = cell_id > ncellsdiv2 ? HIGH_VALUE : LOW_VALUE;
  }
  *nsize = nsize_out;
  return local_energy;
}

double global_kahan_sum(MPI_Comm comm, int nsize, double *local_energy) {
  struct esum_type local;
  local.sum = 0.0;
  local.correction = 0.0;
  for (int i = 0; i < nsize; i++) {
    double c_next = local_energy[i] + local.correction;
    double new_sum = local.sum + local.correction;
    local.correction = c_next - (new_sum - local.sum);
    local.sum = new_sum;
  }
  struct esum_type global;
  MPI_Allreduce(&local, &global, 1, EPSUM_TWO_DOUBLES, KAHAN_SUM, comm);
  return global.sum;
}

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  int rank, nprocs;
  MPI_Comm comm = MPI_COMM_WORLD;

  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &nprocs);
  if (rank == 0) {
    printf("Total procs %d\n", nprocs);
  }
  init_kahan_sum();

  for (int p = 8; p < 31; p++) {
    long ncells = pow((double)2, (double)p);
    long nsize = 0;
    double acc_sum = 0.0;
    double *local_energy =
        init_energy(rank, nprocs, ncells, &nsize, &acc_sum, comm);
    struct timespec cpu_timer;
    cpu_timer_start(&cpu_timer);
    double dist_sum = global_kahan_sum(comm, nsize, local_energy);
    double time_diff = cpu_timer_stop(cpu_timer);
    double closed_sum = ncells;
    if (rank == 0) {
      double sum_diff = dist_sum - acc_sum;
      printf("  ncells %ld log %d accurate sum %-17.16lg sum %-17.16lg ",
             ncells, (int)log2((double)ncells), acc_sum, dist_sum);
      printf("diff %10.4lg relative diff %10.4lg runtime %lf\n", sum_diff,
             sum_diff / acc_sum, time_diff);
      printf("Accurate sum:%lf\tDist sum:%lf\tTime:%lf\n", acc_sum, dist_sum,
             time_diff);
    }
    free(local_energy);
  }
  MPI_Type_free(&EPSUM_TWO_DOUBLES);
  MPI_Op_free(&KAHAN_SUM);
  MPI_Finalize();
  return 0;
}
