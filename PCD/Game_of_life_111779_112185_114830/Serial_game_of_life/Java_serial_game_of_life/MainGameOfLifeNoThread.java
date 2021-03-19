package game_of_life_no_thread;

import java.util.Random;

public class MainGameOfLifeNoThread {

	public static int tableSize = 2048; //square matrix side size
	
	public static int generations = 2000; //amount of generations
	 
	public static int intervalGenPrint = 100;	//generation print interval
		
	public static long loop_start=0;	//start timer for loop
	public static long loop_end=0;	//end timer for loop
	
	public static long start = 0;	//start timer for program
	public static long end = 0;	//start timer for program
		
	public static int[][] grid = new int[tableSize][tableSize];	//current generation
	public static int[][] newgrid = new int[tableSize][tableSize];	//next generation
	
	public static int alive_cells;	//alive cells per generation
	
	//matrix print
	private void printMatrix(int m[][]) {
		for(int i=0; i<tableSize; i++) {
			for(int j=0; j<tableSize; j++) {
				System.out.print(m[i][j]+" ");
			}
		System.out.println();
		}
	}
	
	//matrix fill (ONLY grid[][])
	private static void fillMatrix() {
		Random gerador = new Random(1985);
		for(int i=0; i<tableSize; i++) {
			for(int j=0; j<tableSize; j++) {
				grid[i][j] = gerador.nextInt(2147483647) % 2;
			}
		}
	}
	
	//matrix copy (ONLY newgrid[][] to grid[][])
	private static void copyMatrix() {
		for(int i=0; i<tableSize; i++) {
			for(int j=0; j<tableSize; j++) {
				grid[i][j]=newgrid[i][j];
			}
		}
	}
	
	//get alive neighbors of a cell
	private static int getNeighbors(int i, int j){
		int prev_row=0, next_row=0, prev_col=0, next_col=0, neighbor_alive=0;

	    prev_row=(i-1+tableSize)%tableSize;
	    next_row=(i+1)%tableSize;
	    prev_col=(j-1+tableSize)%tableSize;
	    next_col=(j+1)%tableSize;

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
		
	//game of life
	private static void gameOfLife() {
		
		loop_start = System.currentTimeMillis();
		
		for(int gen=0; gen<=generations; gen++) {
			
			int neighbor_alive=0;
									
			for(int i=0; i<tableSize; i++) {
				for(int j=0; j<tableSize; j++) {
					if(grid[i][j]==1) {
						alive_cells++;
					}
					
					neighbor_alive=getNeighbors(i, j);
					
					//Simple debugger
					//System.out.println(Thread.currentThread().getName()+" >> I'm ["+ i +"]["+j+"] -> "+grid[i][j]
					//		+" I have "+neighbor_alive+" alive neighbors");
					
					
					//predefined rules
	                //"Células vivas com menos de 2 (dois) vizinhas vivas morrem por abandono;
	                // Cada célula viva com 2 (dois) ou 3 (três) vizinhos deve permanecer viva para a próxima geração;
	                // Cada célula viva com 4 (quatro) ou mais vizinhos morre por superpopulaçãoo.
	                // Cada célula morta com exatamente 3 (três) vizinhos deve se tornar viva."
					if(grid[i][j]==1){
						//System.out.println(Thread.currentThread().getName()+" >> I'm ["+ i +"]["+j+"] -> "+grid[i][j]
								//+" I have "+neighbor_alive+" alive neighbors");
	                    if(neighbor_alive<2 || neighbor_alive>3) newgrid[i][j] = 0;
	                    else newgrid[i][j] = grid[i][j];
	                }
	                else{
	                    if(neighbor_alive == 3) newgrid[i][j] = 1;
	                    else newgrid[i][j] = grid[i][j];
	                }
				}
			}				
			
			if (gen == 0 && generations==0) System.out.printf("Geração inicial (geração única)\t: %d células vivas\n", alive_cells);
			else if (gen == 0) System.out.printf("Geração inicial\t: %d células vivas\n", alive_cells);
			else if (gen == 1 && generations>=2) System.out.printf("Geração %d\t: %d células vivas\n", gen, alive_cells);
			else if (gen == generations) System.out.printf("Última geração\t: %d células vivas \t(%d iterações)", alive_cells, generations);
            else if ((gen%intervalGenPrint == 0) && (gen>=intervalGenPrint)) System.out.printf("Geração %d\t: %d células vivas\n", gen, alive_cells);
						
			//update generation matrix grid
			//multithread in funtcion
			copyMatrix();		
			
			alive_cells=0;
			
		}
		loop_end = System.currentTimeMillis();
	}
	
	
	public static void main(String args[]) {
		System.out.printf("System Specs");
		System.out.printf("\nProcessor: Intel Core i3-8100 (6 MB Cache / 4 Cores / 4 Threads)");
		System.out.printf("\nRAM: 16 GB / 2400 MHz\n");
		System.out.printf("OS: Ubuntu 18.04\n\n");
		
		start = System.currentTimeMillis();
        
		fillMatrix();
		
        gameOfLife();       
        
        System.out.println("\n\nThreads execution time: "+(long)(loop_end - loop_start)+" ms (NO THREADS");
        end = System.currentTimeMillis();
        System.out.println("Total execution time: "+(long)(end-start)+" ms\n");
	}
	
}

