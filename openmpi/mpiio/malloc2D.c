#include "malloc2D.h"
#include "stdlib.h"

double **malloc2D(int jmax, int imax){
  int totalCells = jmax*imax;
  int totalRowPtrs = jmax;
  double **x = (double **)malloc(totalRowPtrs*sizeof(double*)+totalCells*sizeof(double));
  x[0] = (double *)(x+totalRowPtrs);
  for(int i = 1; i < totalRowPtrs; i++){
    x[i] = x[i-1]+imax;
  }
  return (x);
}
