#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
  if (argv[1] == NULL){
    printf("Matrix dimensions not specified.\n");
    exit(1);
  } else if (argv[2] == NULL) {
    printf("Assuming square matrix.\n");
    argv[2] = argv[1];
  }
  int rows = atoi(argv[1]);
  int cols = atoi(argv[2]);
  /* Matrix A dimensions initialization ---------------------------*/
  double *mA, *mC;

  mA = (double *)malloc(cols*rows*sizeof(double));
  mC = (double *)malloc(cols*cols*sizeof(double));
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      mA[i*cols + j] = (rand()%100)/100.0;
    }
  }
  /* A'*A matrix multiplication -----------------------------------*/
  if (rows*cols <= 4096) {
    FILE *f = fopen("../serial/data.txt", "w");
    if (f == NULL) {
      printf("Error: failed to open file.\n");
      exit(1);
    }

    for (int i = 0; i < cols; i++){
      for (int j = 0; j < cols; j++){
        mC[i*cols + j] = 0.0;
        for (int k = 0; k < rows; k++){
          mC[i*cols + j] += mA[k*cols + i] * mA[k*cols + j];
        }
        fprintf(f, "%1.4f ", mC[i*cols + j]);
      }
      fprintf(f, ";\n");
    }
  } else {
    for (int i = 0; i < cols; i++){
      for (int j = 0; j < cols; j++){
        mC[i*cols + j] = 0.0;
        for (int k = 0; k < rows; k++){
          mC[i*cols + j] += mA[k*cols + i] * mA[k*cols + j];
        }
      }
    }
  }
  printf("Task complete!\n");
  return 0;
}
