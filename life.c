#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphics.h"

#define MAX_GEN 100

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

void next_gen(int N, int** state, int** state_new){
  //get neighbours
  //get first row
  for(int i=1; i < N+1; i++){
    for(int j=1; j < N+1; j++){
      int num_neighbours= state[i-1][j-1] + state[i-1][j] + state[i-1][j+1] +
      state[i][j-1] +state[i][j+1] +state[i+1][j-1] +state[i+1][j]
      +state[i+1][j+1];
      if(state[i][j]==1){
        //cell is on, if 2 n or 3 stays on otherwise dies
        state_new[i][j]=1;
        if(num_neighbours !=2  && num_neighbours != 3)
          state_new[i][j]=0;
      }else{
        state_new[i][j]=0;
        //cell is off, turn on if 3 neighbours
        if(num_neighbours ==3){
          state_new[i][j]=1;
        }
      }
    }
  }
}
int main(int argc, char const *argv[]) {
  if(argc != 2){
    printf("Invalid number of inputs, we need: filename \n");
    return -1;
  }
  const char* filename = argv[1];
  printf("We are using input from: %s\n", filename);
  int N = 50;
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

  //next generation function, calculates state in the new generation
  int*** p_state = &state;
  int*** p_state_new = &state_new;
  for(int j=0;j< MAX_GEN; j++){
    printf("Gen: %d \n", j);
    // printf("Original state:  \n");
    display(N, *p_state);
    next_gen(N, *p_state, *p_state_new);
    // printf("Next generation: \n");
    // display(N, state_new);
    // printf("Next generation from pointer (should be the same): \n");
    // display(N, *p_state_new);
    //point state to new state and
    //state_new to state as not to malloc anything else
    int ***aux;
    aux = p_state;
    p_state = p_state_new;
    p_state_new = aux;
    // printf("After the swap we have: \n");
    // printf("This is the new var: state\n");
    // display(N, *p_state);
    // printf("This is the new var: new_state\n");
    // display(N, *p_state_new);
  }


  //free arrays
  for(int i=0; i< N+2; i++){
    free(state[i]);
    free(state_new[i]);
  }
  free(state);
  free(state_new);
  free(p_state);
  free(p_state_new);

  return 0;
}
