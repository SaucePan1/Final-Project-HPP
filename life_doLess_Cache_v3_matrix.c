/*
Version of life with graphics.

To compile include the flags: -I/usr/X11R6/include -L/usr/X11R6/lib -lX11
And link to graphics.c


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

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

void read_data_transposed(const char* filename, int** state, int N){
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
    //this is transposed
    state[k+1][j+1]=1;
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


void next_gen(int N, int** state, int** state_new, int** v3_neighbours, int** v3_neighbours_next){
  //get neighbours
  //get first row
  for(int i=1; i < N+1; i++){
    int j=1;
    int v1 = 0, v2 = state[i-1][j] + state[i+1][j];
    for(j=1; j < N+1; j++){
      //get v3
      int v3 = state[i-1][j+1] + state[i][j+1] + state[i+1][j+1];
      int v3_n = v3_neighbours[i][j];
      if(v3_n != v3){ printf("there is a bug at v3 %d, %d", i,j);}

      int num_neighbours= v1+v2+v3;
      //printf("%d %d n %d \n", i, j, num_neighbours);
      //Update the Cell
      if(state[i][j]==1){
        //cell is on, if 2 n or 3 stays on otherwise dies
        //we correct v2
        v2++;
        if(num_neighbours !=2  && num_neighbours != 3){
          //i, j died we change the state and update the neighbour matrix
          state_new[i][j]=0;
          //Following cells lost a v3 neighbour:
          v3_neighbours_next[i-1][j-1]--;
          v3_neighbours_next[i][j-1]--;
          v3_neighbours_next[i+1][j-1]--;
        }else{
          state_new[i][j]=1;
        }
      }else{
        state_new[i][j]=0;
        //cell is off, turn on if 3 neighbours
        if(num_neighbours ==3){
          //new birth, set new state and update neighbours
          state_new[i][j]=1;
          //Following cells gained a v3 neighbour:
          v3_neighbours_next[i-1][j-1]++;
          v3_neighbours_next[i][j-1]++;
          v3_neighbours_next[i+1][j-1]++;
        }
      }
      v1 = v2;
      v2 = v3 - state[i][j+1];
    }
  }
}

void construct_v3_neighbours(int N, int** state, int** v3_neighbours, int** v3_neighbours_new){
    //NEIGHBOUR MATRIX IS TRANSPOSED SINCE IS ACCESSED BY COLUMNS
    //First we do without transposing
    //Acces by columns so its faster
    for(int i=1; i<N+1; i++){
      for(int j=1; j<N+1; j++){
        v3_neighbours[i][j] = state[i-1][j+1] + state[i][j+1] + state[i+1][j+1];
        v3_neighbours_new[i][j] = state[i-1][j+1] + state[i][j+1] + state[i+1][j+1];
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
    //allocate memory for both
    state[i]=(int*)malloc(sizeof(int)*(N+2));
    state_new[i]=(int*)malloc(sizeof(int)*(N+2));
    //set state to 0
    memset(state[i], 0, sizeof(int)*(N+2));
    memset(state_new[i], 0, sizeof(int)*(N+2));
  }

  //Allocate memory for v3 matrix
  int** v3_neighbours = (int**)malloc(sizeof(int*)*(N+2));
  int** v3_neighbours_new = (int**)malloc(sizeof(int*)*(N+2));
  for(int i=0; i<N+2;i++){
    //allocate memory for both
    v3_neighbours[i]=(int*)malloc(sizeof(int)*(N+2));
    v3_neighbours_new[i]=(int*)malloc(sizeof(int)*(N+2));
    //set state to 0
    memset(v3_neighbours[i], 0, sizeof(int)*(N+2));
    memset(v3_neighbours_new[i], 0, sizeof(int)*(N+2));
  }
  read_data(filename, state, N);
  read_data(filename, state_new, N);

  printf("Constructing v3_neighbours ... \n");
  construct_v3_neighbours(N, state, v3_neighbours, v3_neighbours_new);
  printf("Finished constructing v3_neighbours ... \n");
  int*** p_state = &state;
  int*** p_state_new = &state_new;
  for(int j=0;j< MAX_GEN; j++){
    //printf("Gen: %d \n", j);
    // printf("Original state:  \n");
    if(disp){display(N, *p_state);}
    next_gen(N, *p_state, *p_state_new, v3_neighbours, v3_neighbours_new);
    int ***aux;
    aux = p_state;
    p_state = p_state_new;
    p_state_new = aux;
    //Copy neighbour matrix
    for(int i=1; i<N+1; i++){
      memcpy(v3_neighbours[i], v3_neighbours_new[i], sizeof(int)*(N+2));
    }

  }

  //free arrays
  for(int i=0; i< N+2; i++){
    free(state[i]);
    free(state_new[i]);
    free(v3_neighbours[i]);
    free(v3_neighbours_new[i]);
  }
  free(state);
  free(state_new);
  free(v3_neighbours);
  free(v3_neighbours_new);


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
