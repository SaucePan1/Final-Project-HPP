/*
Version of life with graphics.

To compile include the flags: -I/usr/X11R6/include -L/usr/X11R6/lib -lX11
And link to graphics.c


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define blockSz 200
//for testing 200
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
void display_temp(int N, int** state){
  for(int i =0; i<N; i++){
    for(int j=0; j< N; j++){
      if(state[i][j] == 0)
        printf(" -");
      else
        printf(" o");
    }
    printf("\n");
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
  return;
}

// void DrawCell(int i, int j, int N, int L, int W){
//   float dx = 1/(float)N;
//   float dy = dx;
//   float cellWidth = dx;
//   float x = dx*j - dx/2;
//   float y = 1 - dx*i -dy/2; //as to preserve same order as matrix (0,0) on top
//   DrawRectangle(x,y, L, W, cellWidth, cellWidth, cellColor);
//   return;
// }


// void updateCell(int i, int j, int num_neighbours, int** state, int** state_new){
//   if(state[i][j]==1){
//     //cell is on, if 2 n or 3 stays on otherwise dies
//     if(num_neighbours !=2  && num_neighbours != 3){
//       state_new[i][j]=0;
//     }else{
//       state_new[i][j]=1;
//     }
//   }else{
//     state_new[i][j]=0;
//     //cell is off, turn on if 3 neighbours
//     if(num_neighbours ==3){
//       state_new[i][j]=1;
//     }
//   }
// return;
// }

void UpdateCellsOnBlock(int iStart, int iEnd, int jStart, int jEnd,
  int **state, int** state_new, int** temp){

  //We need padding!
  for(int i = 0; i<blockSz+2; i++){
    memcpy(temp[i], &state[iStart+i-1][jStart-1], sizeof(int)*(blockSz+2));
  }
  int max_i = iEnd-iStart;
  int max_j = jEnd-jStart;
  //implement algorithm as usual
  for(int i=1; i < max_i+1; i++){
    int j=1;
    int v1 = temp[i-1][j-1] + temp[i][j-1]+ temp[i+1][j-1];
    //int v1 = 0;
    int v2 = temp[i-1][j] + temp[i+1][j];
    for(j=1; j < max_j+1; j++){
      //get v3
      int v3 = temp[i-1][j+1] + temp[i][j+1] + temp[i+1][j+1];
      int num_neighbours= v1+v2+v3;
      //Update the Cell
      if(temp[i][j]==1){
        //cell is on, if 2 n or 3 stays on otherwise dies
        //we correct v2
        v2++;
        if(num_neighbours !=2  && num_neighbours != 3){
          state_new[iStart -1 +i][jStart -1 +j]=0;
        }else{
          state_new[iStart -1 +i][jStart -1 +j]=1;
        }
      }else{
        state_new[iStart -1 +i][jStart -1 +j]=0;
        //cell is off, turn on if 3 neighbours
        if(num_neighbours ==3){
          state_new[iStart -1 +i][jStart -1 +j]=1;
        }
      }
      v1 = v2;
      v2 = v3 - temp[i][j+1];
    }
  }
  return;
}


void next_gen(int N, int** state, int** state_new, int** temp){
  if(N%blockSz != 0){printf("BlockSz does not divide N!\n"); return;}
  // printf("Display state: \n");
  // display(10, state);
  int iStart;
  for(iStart=1; iStart<N+1; iStart+=blockSz){
    int iEnd = iStart+blockSz;
    int jStart;
    for(jStart = 1; jStart<N+1; jStart += blockSz){
      int jEnd = jStart+blockSz;
      //printf("Calling Update with iStart= %d, jStart = %d \n", iStart, jStart);
      UpdateCellsOnBlock(iStart, iEnd, jStart, jEnd,
         state, state_new, temp);
    }
  }
  return;
}

int main(int argc, char const *argv[]) {

  if(argc != 5){
    printf("Invalid number of inputs, we need: N MAX_GEN display filename \n");
    return -1;
  }
  int N = atoi(argv[1]);
  int MAX_GEN = atoi(argv[2]);
  int disp= atoi(argv[3]);
  const char* filename = argv[4];
  //printf("We are using input from: %s\n", filename);

  struct timeval tini, tfin;
  gettimeofday(&tini,0);
  //Program starts:

  //CELL NUMBER for testing 4000
  int** state = (int**)malloc(sizeof(int*)*(N+2));
  int** state_new = (int**)malloc(sizeof(int*)*(N+2));
  for(int i=0; i<N+2;i++){
    //allocate memory for bboth
    state[i]=(int*)malloc(sizeof(int)*(N+2));
    state_new[i]=(int*)malloc(sizeof(int)*(N+2));
    //set state to 0
    memset(state[i], 0, sizeof(int)*(N+2));
    memset(state_new[i], 0, sizeof(int)*(N+2));
  }
  //allocate mem for the temp block
  int** temp = (int**)malloc(sizeof(int*)*(blockSz+2));
  for(int i=0; i<blockSz+2; i++){
    temp[i]=(int*)malloc(sizeof(int)*(blockSz+2));
  }
  read_data(filename, state, N);
  read_data(filename, state_new, N);

  //next generation function, calculates state in the new generation
  int*** p_state = &state;
  int*** p_state_new = &state_new;
  for(int j=0;j< MAX_GEN; j++){
    //printf("Gen: %d \n", j);
    // printf("Original state:  \n");

    if(disp){display(N, *p_state);}
    next_gen(N, *p_state, *p_state_new, temp);
    //UpdateCellsOnBlock(1, N+1, 1, N+1, *p_state, *p_state_new, temp);
    int ***aux;
    aux = p_state;
    p_state = p_state_new;
    p_state_new = aux;

  }

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
