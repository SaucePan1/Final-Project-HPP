#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_matrix(int** mat, int N, int M){
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      printf("%d", mat[i][j]);
    }
    printf("\n");
  }
  return;
}
int main(int argc, char const *argv[]) {
  int N=5;
  int**A = (int**)malloc(sizeof(int*)*N);
  int**B = (int**)malloc(sizeof(int*)*N);
  for(int i=0; i<N; i++){
      A[i]=(int*)malloc(sizeof(int)*N);
      B[i]=(int*)malloc(sizeof(int)*N);
      memset(A[i], 0, sizeof(int)*N);
      memset(B[i], '1', sizeof(int)*N);
  }

  printf("Original A: \n");
  print_matrix(A,N,N);
  printf("Original B: \n");
  print_matrix(B,N,N);

  int***Ap = &A;
  int***Bp =&B;

  printf("A from pointer: \n");
  print_matrix(*Ap, N,N);
  printf("B from pointer: \n");
  print_matrix(*Bp, N,N);

  int***t= Ap;
  Ap = Bp;
  Bp = t;

  printf("A from pointer: \n");
  print_matrix(*Ap, N,N);
  printf("B from pointer: \n");
  print_matrix(*Bp, N,N);

  *Bp[0][0]=1;
  printf("A from pointer: \n");
  print_matrix(*Ap, N,N);
  printf("B from pointer: \n");
  print_matrix(*Bp, N,N);

  t= Ap;
  Ap = Bp;
  Bp = t;


  printf("A from pointer: \n");
  print_matrix(*Ap, N,N);
  printf("B from pointer: \n");
  print_matrix(*Bp, N,N);
  return 0;
}
