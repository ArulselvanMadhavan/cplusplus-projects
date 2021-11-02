#include "malloc2D.h"
#include <stdlib.h>

double **malloc2D(int jmax, int imax, int joffset, int ioffset) {
  int rowPtrs = jmax * sizeof(double *);
  int cells = jmax * imax * sizeof(double);
  int totalSize = rowPtrs + cells;
  double **x = (double **)malloc(totalSize);
  double **totalRowPtrs = x + jmax;
  x[0] = (double *)(totalRowPtrs + ioffset); /* offset by ioffset so x[-1], x[-2] etc., are halo cells */
  for (int j = 1; j < jmax; j++) {
    x[j] = x[j - 1] + imax;
  }
  x += joffset;
  return x;
}

void malloc2D_free(double **x, int joffset) {
  x -= joffset;
  free(x);
}
