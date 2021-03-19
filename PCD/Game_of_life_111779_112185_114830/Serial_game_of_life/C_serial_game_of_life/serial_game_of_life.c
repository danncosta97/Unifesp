#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <locale.h>

//square matrix side size
#define TABLE_SIZE 2048

//amount of generations
#define GENERATIONS 2000

//print generations by an interval of #GEN_PRINT_INTERVAL
//(ex: 5 -> (0,1,5,10,15,20,...,#GENERATIONS-1))
//(ex: 15 -> (0,1,15,30,45,60,...,#GENERATIONS-1))
#define GEN_PRINT_INTERVAL 100

//value to use in srand()
#define SRAND_VALUE 1985

void gen_matrix(int ***M, int m, int n){
    *M = (int**) malloc(m * sizeof(int*));
    for(int i=0; i<n; i++){
        (*M)[i] = (int*) malloc(n * sizeof(int));
    }
}

void init_matrix(int **grid, int m, int n){
    srand(SRAND_VALUE);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = rand() % 2;
        }
    }
}

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

void game_of_life(int **grid,int **newgrid, int m, int n, int *alive_cells){

    int prev_row=0, next_row=0, prev_col=0, next_col=0, neighbor_alive=0;
    //printf("CURRENT\n");
    //print_matrix(grid,m,n);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j]==1) (*alive_cells)++;

            neighbor_alive=getNeighbors(grid, i, j);

            //neighbors_check_end

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
    copy_matrix(grid, newgrid, m, n); //update gen
}

int main(){

    printf("System Specs");
    printf("\nProcessor: Intel Core i3-8100 (6 MB Cache / 4 Cores / 4 Threads)");
    printf("\nRAM: 16 GB / 2400 MHz\n");
    printf("OS: Windows 10\n\n");

    struct timeval start, end;  //counters
    struct timeval loop_time_start, loop_time_end;  //loop counters

    gettimeofday(&start, NULL);    //program starts

    setlocale(LC_ALL, "Portuguese");    //keyboard settings

    int **grid, **newgrid, m=0, n=0, alive_cells=0, elapsed_time=0, loop_elapsed_time=0;

    m=n=TABLE_SIZE; //rows (m) and columns (n)

    gen_matrix(&grid,m,n);
    gen_matrix(&newgrid,m,n);
    init_matrix(grid,m,n);

    gettimeofday(&loop_time_start, NULL);    //loop starts
    for(int gen=0; gen<=GENERATIONS; gen++){
        game_of_life(grid, newgrid, m, n, &alive_cells);
        if (gen == 0 && GENERATIONS==0) printf("Geração inicial (geração única)\t: %d células vivas\n", alive_cells);
        else if (gen == 0) printf("Geração inicial\t: %d células vivas\n", alive_cells);
        else if (gen == 1 && GENERATIONS>=2) printf("Geração %d\t: %d células vivas\n", gen, alive_cells);
        else if (gen == GENERATIONS) printf("Última geração\t: %d células vivas \t(%d iterações)", alive_cells, GENERATIONS);
        else if ((gen%GEN_PRINT_INTERVAL == 0) && (gen>=GEN_PRINT_INTERVAL)) printf("Geração %d\t: %d células vivas\n", gen, alive_cells);
        alive_cells=0;
    }

    gettimeofday(&loop_time_end, NULL);    //loop ends

    loop_elapsed_time = ((loop_time_end.tv_sec * 1000000 + loop_time_end.tv_usec)
                    - (loop_time_start.tv_sec * 1000000 + loop_time_start.tv_usec))/1000;

    gettimeofday(&end, NULL);    //program ends

    elapsed_time = ((end.tv_sec * 1000000 + end.tv_usec)
                    - (start.tv_sec * 1000000 + start.tv_usec))/1000;

    printf ("\n\nLoop execution time: %u ms (WITHOUT THREADS)", loop_elapsed_time);

    printf ("\nTotal execution time: %u ms\n", elapsed_time);

    return 0;
}
