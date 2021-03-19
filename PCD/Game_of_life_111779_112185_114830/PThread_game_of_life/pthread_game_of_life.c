#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <locale.h>

//square matrix side size
#define TABLE_SIZE 2048

//generations
#define GENERATIONS 2000

//print generations by an interval of #GEN_PRINT_INTERVAL
//(ex: 5 -> (0,1,5,10,15,20,...,#GENERATIONS-1))
//(ex: 15 -> (0,1,15,30,45,60,...,#GENERATIONS-1))
#define GEN_PRINT_INTERVAL 100

//number of threads
#define NUM_THREADS 8

//value to use in srand()
#define SRAND_VALUE 1985

pthread_t t[NUM_THREADS];
pthread_mutex_t mutex;
pthread_barrier_t barrier;

int alive_cells = 0; //total alive cells in one generation

struct timeval threads_start, threads_end;  //thread counters

struct thread_data{
  int **grid;   //current gen
  int **newgrid; //new gen
  int m;    //rows
  int n;    //columns
  int thread_id;
  int t_alive_cells;    //thread alive cells
};

//create matrixes
void gen_matrix(int ***M, int m, int n){
    *M = (int**) malloc(m * sizeof(int*));
    for(int i=0; i<n; i++){
        (*M)[i] = (int*) malloc(n * sizeof(int));
    }
}

//initialize matrixes with rand
void init_matrix(int **grid, int m, int n){
    srand(SRAND_VALUE);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = rand() % 2;
        }
    }
}

//copy matrix grid to matrix newgrid
void copy_matrix(int **grid, int **newgrid, int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = newgrid[i][j];
        }
    }
}

void print_matrix(int **M, int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            printf("%d ",M[i][j]);
        }
        printf("\n");
    }
}

//returns amount of neighbors alive
int getNeighbors(int** grid, int i, int j){

    int prev_row=0, next_row=0, prev_col=0, next_col=0, neighbor_alive=0;

    prev_row=(i-1+TABLE_SIZE)%TABLE_SIZE;
    next_row=(i+1)%TABLE_SIZE;
    prev_col=(j-1+TABLE_SIZE)%TABLE_SIZE;
    next_col=(j+1)%TABLE_SIZE;

    //neighbors_check
    if(grid[prev_row][prev_col] == 1) neighbor_alive++;
    if(grid[prev_row][j] == 1) neighbor_alive++;
    if(grid[prev_row][next_col] == 1) neighbor_alive++;
    if(grid[(i)][prev_col] == 1) neighbor_alive++;
    if(grid[(i)][next_col] == 1) neighbor_alive++;
    if(grid[next_row][prev_col] == 1) neighbor_alive++;
    if(grid[next_row][j] == 1) neighbor_alive++;
    if(grid[next_row][next_col] == 1) neighbor_alive++;

    return neighbor_alive;
}

void *game_of_life(void *args){

    int neighbor_alive=00,local_alive_cells=0;

    struct thread_data *targs = args;

    int m = targs->m;
    int n = targs->n;
    int **grid =  targs->grid;
    int **newgrid = targs->newgrid;
    int fake_pid = targs->thread_id;

    gettimeofday(&threads_start, NULL);;  //threads/main loop starts
    pthread_barrier_wait(&barrier); //sync threads

    for (int gen=0; gen <= GENERATIONS; gen++){
        local_alive_cells=0;

        //divide amount of lines for each thread
        for (int i = fake_pid*TABLE_SIZE/NUM_THREADS; i < (fake_pid+1)*TABLE_SIZE/NUM_THREADS; i++){
            for (int j = 0; j < TABLE_SIZE; j++){
                if(grid[i][j]==1)   local_alive_cells++;

                neighbor_alive=getNeighbors(grid, i, j);

                //debug checker
                /*
                printf("I'm [%d][%d]", i, j);
                printf("\n [%d][%d] -> %d", prev_row, prev_col, grid[prev_row][prev_col]);
                printf("\n [%d][%d] -> %d", prev_row, j, grid[prev_row][j] == 1);
                printf("\n [%d][%d] -> %d", prev_row, next_col, grid[prev_row][next_col]);
                printf("\n [%d][%d] -> %d", i, prev_col, grid[(i)][prev_col]);
                printf("\n [%d][%d] -> %d", i, next_col, grid[(i)][next_col]);
                printf("\n [%d][%d] -> %d", next_row, prev_col, grid[next_row][prev_col]);
                printf("\n [%d][%d] -> %d", next_row, j, grid[next_row][j]);
                printf("\n [%d][%d] -> %d", next_row, next_col, grid[next_row][next_col]);
                printf("\nAlive: %d\n",neighbor_alive);
                */

                //predefined rules
                //"C√©lulas vivas com menos de 2 (dois) vizinhas vivas morrem por abandono;
                // Cada c√©lula viva com 2 (dois) ou 3 (tr√™s) vizinhos deve permanecer viva para a pr√≥xima gera√ß√£o;
                // Cada c√©lula viva com 4 (quatro) ou mais vizinhos morre por superpopula√ß√£o.
                // Cada c√©lula morta com exatamente 3 (tr√™s) vizinhos deve se tornar viva."
                if(grid[i][j]==1){
                    if(neighbor_alive<2 || neighbor_alive>3) newgrid[i][j] = 0;
                    else newgrid[i][j] = grid[i][j];
                }
                else{
                    if(neighbor_alive == 3) newgrid[i][j] = 1;
                    else newgrid[i][j] = grid[i][j];
                }
            }
        }
        //printf("\n[%d] fake_pid([%d]) Alive local Cells: %d", gen, fake_pid, local_alive_cells); //alive cells per thread

        pthread_barrier_wait(&barrier); //sync threads

        //mutex blocks possibles overwrite
        pthread_mutex_lock(&mutex);
        alive_cells = alive_cells + local_alive_cells; //one by one, threads add value to TOTAL alive_cells
        pthread_mutex_unlock(&mutex);

        pthread_barrier_wait(&barrier); //sync threads

        //'if' ensures not repeated operations by all threads (could be any thread on 'if' parameter)
        if( fake_pid == NUM_THREADS-1 ) {
				if (gen == 0 && GENERATIONS==0) printf("GeraÁ„o inicial (geraÁ„o ˙nica)\t: %d cÈlulas vivas\n", alive_cells);
				else if (gen == 0) printf("GeraÁ„o inicial\t: %d cÈlulas vivas\n", alive_cells);
				else if (gen == 1 && GENERATIONS>=2) printf("GeraÁ„o %d\t: %d cÈlulas vivas\n", gen, alive_cells);
				else if (gen == GENERATIONS) printf("⁄ltima geraÁ„o\t: %d cÈlulas vivas \t(%d iteraÁıes)", alive_cells, GENERATIONS);
                else if ((gen%GEN_PRINT_INTERVAL == 0) && (gen>=GEN_PRINT_INTERVAL)) printf("GeraÁ„o %d\t: %d cÈlulas vivas\n", gen, alive_cells);
                //printf("\n");
                //print_matrix(grid, TABLE_SIZE, TABLE_SIZE);
                //printf("\n");
                //print_matrix(newgrid, TABLE_SIZE, TABLE_SIZE);
                //printf("\n");
                copy_matrix(grid, newgrid, TABLE_SIZE, TABLE_SIZE);
        }

        pthread_barrier_wait(&barrier); //sync threads

        //all threads make alive_cells=0, but all them are synced right after that
        //so, none of them are going to interfere any results
        if(alive_cells!=0) alive_cells=0;

        pthread_barrier_wait(&barrier); //sync threads
    }
    gettimeofday(&threads_end, NULL);  //threads/main loop ends
}

int main(){

    printf("System Specs");
    printf("\nProcessor: Intel Core i3-8100 (6 MB Cache / 4 Cores / 4 Threads)");
    printf("\nRAM: 16 GB / 2400 MHz\n");
    printf("OS: Ubuntu 18.04\n\n");

    struct timeval start, end;  //counters

    gettimeofday(&start, NULL);    //program starts

    setlocale(LC_ALL, "Portuguese");    //keyboard settings

    int **grid, **newgrid, m=0, n=0, elapsed_time=0, elapsed_time_threads=0;

    m=n=TABLE_SIZE; //rows (m) and columns (n)

    gen_matrix(&grid,m,n);
    gen_matrix(&newgrid,m,n);
    init_matrix(grid,m,n);

    // each position to each thread -> SEE thread_data
    struct thread_data t_array[NUM_THREADS];

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("\n-- Mutex initialization failed --\n");
        return 1;
    }


    if (pthread_barrier_init (&barrier, NULL, NUM_THREADS) != 0) {
        printf("\n-- Barrier initialization failed --\n");
        return 1;
    }

    //thread creations
    for(int i=0; i<NUM_THREADS; i++) {
        t_array[i].grid = grid;
        t_array[i].newgrid = newgrid;
        t_array[i].m = m;
        t_array[i].n = n;
        t_array[i].thread_id = i;
        t_array[i].t_alive_cells = 0;
        pthread_create(&t[i], NULL, &game_of_life, (void *) &t_array[i]);
    }

    //ensures all threads are finished
    for(int i=0; i<NUM_THREADS; i++) {
        pthread_join(t[i], NULL);
    }



    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier); //destroy barrier


    elapsed_time_threads = ((threads_end.tv_sec * 1000000 + threads_end.tv_usec)
                            - (threads_start.tv_sec * 1000000 + threads_start.tv_usec))/1000;

    printf("\n\nThreads execution time: %u ms (THREADS: %d)", elapsed_time_threads, NUM_THREADS);

    gettimeofday(&end, NULL);
    elapsed_time = ((end.tv_sec * 1000000 + end.tv_usec)
                    - (start.tv_sec * 1000000 + start.tv_usec))/1000;

    printf("\nTotal execution time: %u ms\n", elapsed_time);

    return 0;
}
