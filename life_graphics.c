/*
Version of life with graphics.

To compile include the flags: -I/usr/X11R6/include -L/usr/X11R6/lib -lX11
And link to graphics.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics/graphics.h"

#define MAX_GEN 1000

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
  for(int i=1; i < N+1; i++){
    for(int j=1; j < N+1; j++){
      int num_neighbours= state[i-1][j-1] + state[i-1][j] + state[i-1][j+1] +
      state[i][j-1] +state[i][j+1] +state[i+1][j-1] +state[i+1][j]
      +state[i+1][j+1];
      if(state[i][j]==1){
        //cell is on, if 2 n or 3 stays on otherwise dies
        if(num_neighbours !=2  && num_neighbours != 3){
          state_new[i][j]=0;
        }else{
          state_new[i][j]=1;
          DrawCell(i, j, N, L, W);
        }
      }else{
        state_new[i][j]=0;
        //cell is off, turn on if 3 neighbours
        if(num_neighbours ==3){
          state_new[i][j]=1;
          DrawCell(i, j, N, L, W);
        }
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  float L=1, W=1;

  if(argc != 2){
    printf("Invalid number of inputs, we need: filename \n");
    return -1;
  }
  const char* filename = argv[1];
  printf("We are using input from: %s\n", filename);
  int N = 1000;
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
    printf("Gen: %d \n", j);
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





  return 0;
}
