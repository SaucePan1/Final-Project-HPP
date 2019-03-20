#include <stdio.h>
#include <string.h>

#define I 10
#define J 10

int main(int argc, char const *argv[]) {

  int arr[I][J];
  for(int i=0; i<I; i++){
    for(int j=0; j<J; j++){
      arr[i][j]=j*i;
    }
  }
  int temp[5][5];
  for(int i=0; i<5; i++){
    memcpy(temp[i], &arr[i][5], sizeof(int)*5);
  }

  printf("temp is: \n");
  for(int i=0; i<5; i++){
    for(int j=0; j<5; j++){
      printf("%d ", temp[i][j]);
    }
    printf("\n");
  }
  printf("arr is \n");
  for(int i=0; i<I; i++){
    for(int j=0; j<J; j++){
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
  return 0;
}
