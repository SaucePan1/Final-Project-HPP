#include <stdio.h>

const int n_fig=5;

int main(int argc, char const *argv[]) {
  int N=50, d=100;
  int growth[n_fig][2]= {{25,25},{26,25},{26,24},{26,23}, {27,24}};
  for(int i=0; i <N; i++){
    for(int k=0; k<n_fig; k++){
      printf("%d %d \n",growth[k][0],growth[k][1]);
      growth[k][0]+= d;
      growth[k][1]+= d;
    }
  }
  return 0;
}
