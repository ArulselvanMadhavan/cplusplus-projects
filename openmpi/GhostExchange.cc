#include "malloc2D.h"
#include "mpi.h"
#include "timer.h"
#include <stdio.h>

void haloupdate_test(int nhalo, int corners, int jsize, int isize, int nleft,
                     int nrght, int nbot, int ntop, int jmax, int imax,
                     int nprocy, int nprocx, int do_timing) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
}

double boundarycondition_time;

void boundarycondition_update(double **x, int nhalo, int jsize, int isize,
                              int nleft, int nrght, int nbot, int ntop) {
  
  struct timespec tstart_bc;
  cpu_timer_start(&tstart_bc);
  if (nleft == MPI_PROC_NULL) {
    for (int j = 0; j < jsize; j++) {
      for (int ll = -nhalo; ll < 0; ll++) {
        x[j][ll] = x[j][0];
      }
    }
  }
  if (nrght == MPI_PROC_NULL) {
    for (int j = 0; j < jsize; j++) {
      for (int ll = 0; ll < nhalo; ll++) {
        x[j][isize + ll] = x[j][isize - 1];
      }
    }
  }
  if (nbot == MPI_PROC_NULL){
      for (int ll=-nhalo; ll<0; ll++){
         for (int i = -nhalo; i < isize+nhalo; i++){
            x[ll][i] = x[0][i];
         }
      }
   }
    if (ntop == MPI_PROC_NULL){
      for (int ll=0; ll<nhalo; ll++){
         for (int i = -nhalo; i < isize+nhalo; i++){
            x[jsize+ll][i] = x[jsize-1][i];
         }
      }
   }
   boundarycondition_time += cpu_timer_stop(tstart_bc);
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  int rank, nprocs;
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &nprocs);

  int imax = 2000;
  int jmax = 2000;
  int nprocx = 4;
  int nprocy = 4;
  int nhalo = 2;
  int corners = 0;
  int do_timing = 0;
  // Parse args

  int xcoord = rank % nprocx;
  int ycoord = rank / nprocx;

  int nleft = (xcoord > 0) ? rank - 1 : MPI_PROC_NULL;
  int nrght = (xcoord < nprocx - 1) ? rank + 1 : MPI_PROC_NULL;
  int ntop = (ycoord > 0) ? rank - nprocx : MPI_PROC_NULL;
  int nbot = (ycoord < nprocy - 1) ? rank + nprocx : MPI_PROC_NULL;

  // int ibegin = i
  int i_block = imax / nprocx;
  int j_block = jmax / nprocy;

  int ibegin = i_block * xcoord;
  int iend = i_block * (xcoord + 1);
  int jbegin = j_block * ycoord;
  int jend = j_block * (ycoord + 1);
  int isize = iend - ibegin;
  int jsize = jend - jbegin;

  // printf("Rank:%d\tx:%d\ty:%d\tnl:%d\tnr:%d\tnt:%d\tnb:%d\n", rank, xcoord,
  // ycoord, nleft, nright, ntop, nbot);
  // printf("I:%d,%d\tJ:%d,%d\n",ibegin,iend,jbegin, jend);

  haloupdate_test(nhalo, corners, jsize, isize, nleft, nrght, nbot, ntop, jmax,
                  imax, nprocy, nprocx, do_timing);
  double **x = malloc2D(jsize + 2 * nhalo, isize + 2 * nhalo, nhalo, nhalo);
  double **xnew = malloc2D(jsize + 2 * nhalo, isize + 2 * nhalo, nhalo, nhalo);

  if (!corners) {
    for (int j = -nhalo; j < jsize + nhalo; j++) {
      for (int i = -nhalo; i < isize + nhalo; i++) {
        x[j][i] = 0.0;
      }
    }
  }
  for (int j = 0; j < jsize; j++) {
    for (int i = 0; i < isize; i++) {
      x[j][i] = 5.0;
    }
  }

  int ispan = 5, jspan = 5;
  if (ispan > imax / 2)
    ispan = imax / 2;
  if (jspan > jmax / 2)
    jspan = jmax / 2;
  for (int j = jmax / 2 - jspan; j < jmax / 2 + jspan; j++) {
    for (int i = imax / 2 - ispan; i < imax / 2 + ispan; i++) {
      if (j >= jbegin && j < jend && i >= ibegin && i < iend) {
        x[j - jbegin][i - ibegin] = 400.0;
      }
    }
  }

  boundarycondition_update(x, nhalo, jsize, isize, nleft, nrght, nbot, ntop);

  MPI_Finalize();
  return 0;
}
