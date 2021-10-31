#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);
  int rank, nprocs;
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  FILE *fin;
  unsigned long file_size = 0;
  char *file_content;
  if (rank == 0) {
    fin = fopen("file.in", "r");
    fseek(fin, 0, SEEK_END);
    file_size = ftell(fin);
    file_content = (char *)(malloc((file_size + 1) * (sizeof(char))));
    fseek(fin, 0, SEEK_SET);
    fread(file_content, 1, file_size, fin);
    file_content[file_size] = '\0';
    fclose(fin);
  }
  MPI_Bcast(&file_size, 1, MPI_LONG, 0, comm);
  printf("Rank:%d\t%ld\n", rank, file_size);
  if (rank != 0) {
    file_content = (char *)(malloc((file_size + 1) * (sizeof(char))));
  }
  MPI_Bcast(file_content, file_size, MPI_CHAR, 0, comm);
  char *line = NULL;
  line = strtok(file_content, "\n");
  while (line != NULL) {
    printf("Rank:%d\tLine:%s\n", rank, line);
    line = strtok(NULL, "\n");
  }
  free(file_content);
  MPI_Finalize();
  return 0;
}
