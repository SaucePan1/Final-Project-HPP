/*
Version of life with graphics.

To compile include the flags: -I/usr/X11R6/include -L/usr/X11R6/lib -lX11
And link to graphics.c


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "graphics/graphics.h"

#define MAX_GEN 2000

const int cellColor=0;
const int windowWidth=800;

void read_data(const char* filename, int** state, int N){
  FILE* fp;
  fp = fopen(filename, "r");
  if(fp==NULL){
    printf("Error reading the file \n");
    return;
  }
  int L;
  fscanf(fp, "%d", &L);
  for(int i=0; i<L; i++){
    int j, k;
    fscanf(fp, "%d", &j);
    fscanf(fp, "%d", &k);
    state[j+1][k+1]=1;
  }
  return;
}

void display(int N, int** state){
  for(int i =1; i<N+1; i++){
    for(int j=1; j< N+1; j++){
      if(state[i][j] == 0)
        printf(" -");
      else
        printf(" o");
    }
    printf("\n");
  }
}

void DrawCell(int i, int j, int N, int L, int W){
  float dx = 1/(float)N;
  float dy = dx;
  float cellWidth = dx;
  float x = dx*j - dx/2;
  float y = 1 - dx*i -dy/2; //as to preserve same order as matrix (0,0) on top
  DrawRectangle(x,y, L, W, cellWidth, cellWidth, cellColor);
  return;
}

void next_gen_graph(int N, int** state, int** state_new, int W, int L){
  //get neighbours
  //get first row


}

int main(int argc, char const *argv[]) {
  float L=1, W=1;
  if(argc != 2){
    printf("Invalid number of inputs, we need: filename \n");
    return -1;
  }
  const char* filename = argv[1];
  //printf("We are using input from: %s\n", filename);

  struct timeval tini, tfin;
  gettimeofday(&tini,0);
  //Program starts:

  //CELL NUMBER
  int N = 100;
  int** state = (int**)malloc(sizeof(int*)*(N+2));
  int** state_new = (int**)malloc(sizeof(int*)*(N+2));
  for(int i=0; i<N+2;i++){
    //allocate memory for both
    state[i]=(int*)malloc(sizeof(int)*(N+2));
    state_new[i]=(int*)malloc(sizeof(int)*(N+2));
    //set state to 0
    memset(state[i], 0, sizeof(int)*(N+2));
    memset(state_new[i], 0, sizeof(int)*(N+2));
  }
  read_data(filename, state, N);
  read_data(filename, state_new, N);

  //GRAPHICS
  InitializeGraphics("0",windowWidth,windowWidth);
  SetCAxes(0,1);
  //next generation function, calculates state in the new generation
  int*** p_state = &state;
  int*** p_state_new = &state_new;
  for(int j=0;j< MAX_GEN; j++){
    //printf("Gen: %d \n", j);
    // printf("Original state:  \n");
    ClearScreen();
    //display(N, *p_state);
    next_gen_graph(N, *p_state, *p_state_new, W, L);
    Refresh();
    int ***aux;
    aux = p_state;
    p_state = p_state_new;
    p_state_new = aux;

    usleep(50000); //Sleep so graphics dont go cray
  }
  FlushDisplay();
  CloseDisplay();

  //free arrays
  for(int i=0; i< N+2; i++){
    free(state[i]);
    free(state_new[i]);
  }
  free(state);
  free(state_new);
  gettimeofday(&tfin,0);

  float elapsed_time_sec =(tfin.tv_sec -tini.tv_sec)
                          +(tfin.tv_usec -tini.tv_usec)/1e6;
  //printf("elapsed time: %f\n", elapsed_time_sec);
  FILE* ftime=NULL;
  ftime =fopen("time.txt", "a+");
  if(ftime==NULL){
    printf("Error writing to file\n");
  }else{
    fprintf(ftime, "%f\n",elapsed_time_sec);
  }
  fclose(ftime);
  return 0;
}
