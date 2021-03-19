import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

public class GameOfLife implements Runnable{
	
	public static int threadAmount = 8;	//amount of threads
	
	public static int tableSize = 2048; //square matrix side size
	
	public static int generations = 2000; //amount of generations
	 
	public static int intervalGenPrint = 100;	//generation print interval
	
	public CyclicBarrier barrier = new CyclicBarrier(threadAmount);	//sync barrier for threads
	
	public static long thread_start=0;	//start timer for threads
	public static long thread_end=0;	//end timer for threads
		
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
	private void fillMatrix() {
		Random gerador = new Random(1985);
		for(int i=0; i<tableSize; i++) {
			for(int j=0; j<tableSize; j++) {
				grid[i][j] = gerador.nextInt(2147483647) % 2;
			}
		}
	}
	
	//matrix copy (ONLY newgrid[][] to grid[][])
	private void copyMatrix() {
		for(int i=(int) (Thread.currentThread().getId()%10-1)*tableSize/threadAmount; i<(Thread.currentThread().getId()%10)*tableSize/threadAmount; i++) {
			for(int j=0; j<tableSize; j++) {
				grid[i][j]=newgrid[i][j];
			}
		}
	}
	
	//get alive neighbors of a cell
	private int getNeighbors(int i, int j){
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
	
	//add alive cells calculated by each thread (mutex way)
	public synchronized void aliveCells(int alive_n) {
		alive_cells=alive_cells+alive_n;
	}
	
	//game of life
	private void gameOfLife() {
		
		thread_start = System.currentTimeMillis();
		
		for(int gen=0; gen<=generations; gen++) {
			
			int aliveLocalCells=0;
			int neighbor_alive=0;
			
			
									
			for(int i=(int) (Thread.currentThread().getId()%10-1)*tableSize/threadAmount; i<(Thread.currentThread().getId()%10)*tableSize/threadAmount; i++) {
				for(int j=0; j<tableSize; j++) {
					if(grid[i][j]==1) {
						aliveLocalCells++;
					}
					
					neighbor_alive=this.getNeighbors(i, j);
					
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
						
			//## SYNC THREAD BARRIER ##
			try{
				barrier.await();
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
			catch (BrokenBarrierException e) {
				e.printStackTrace();
			}
			//## SYNC BARRIER END ##
			
			
			//one by one, threads add value to TOTAL alive_cells
			//synchronized
			this.aliveCells(aliveLocalCells);
			
			
			//## SYNC THREAD BARRIER ##
			try{
				barrier.await();
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
			catch (BrokenBarrierException e) {
				e.printStackTrace();
			}
			//## THREADS SYNCED ##
			
			
			//'if' ensures not repeated operations by all threads (could be any thread on 'if' parameter)
			if(Thread.currentThread().getId()%10-1 == 0) {
				if (gen == 0 && generations==0) System.out.printf("Geração inicial (geração única)\t: %d células vivas\n", alive_cells);
				else if (gen == 0) System.out.printf("Geração inicial\t: %d células vivas\n", alive_cells);
				else if (gen == 1 && generations>=2) System.out.printf("Geração %d\t: %d células vivas\n", gen, alive_cells);
				else if (gen == generations) System.out.printf("Última geração\t: %d células vivas \t(%d iterações)", alive_cells, generations);
                else if ((gen%intervalGenPrint == 0) && (gen>=intervalGenPrint)) System.out.printf("Geração %d\t: %d células vivas\n", gen, alive_cells);
			}
			
			
			//## SYNC THREAD BARRIER ##
			try{
				barrier.await();
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
			catch (BrokenBarrierException e) {
				e.printStackTrace();
			}
			//## THREADS SYNCED ##
			
			
			//update generation matrix grid
			//multithread in funtcion
			copyMatrix();		
			
			
			//## SYNC THREAD BARRIER ##
			try{
				barrier.await();
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
			catch (BrokenBarrierException e) {
				e.printStackTrace();
			}
			//## THREADS SYNCED ##
			
			//reset alive cell
			if(Thread.currentThread().getId()%10-1 == 0) {
				alive_cells=0;
				//System.out.println("END OF GENERATION: #"+gen);
				//this.printMatrix(grid);
			}
			
			//## SYNC THREAD BARRIER ##
			try{
				barrier.await();
			}
			catch (InterruptedException e) {
				e.printStackTrace();
			}
			catch (BrokenBarrierException e) {
				e.printStackTrace();
			}
			//## THREADS SYNCED ##
		}
		thread_end = System.currentTimeMillis();
	}
	
	
	@Override
    public void run() {
				
		if(Thread.currentThread().getId()%10-1 == 0) {
			this.fillMatrix();
		}
		
		//## SYNC THREAD BARRIER ##
		try{
			barrier.await();
		}
		catch (InterruptedException e) {
			e.printStackTrace();
		}
		catch (BrokenBarrierException e) {
			e.printStackTrace();
		}
		//## THREADS SYNCED ##
		
		
		thread_start = System.currentTimeMillis();
		
		
		//## SYNC THREAD BARRIER ##
		try{
			barrier.await();
		}
		catch (InterruptedException e) {
			e.printStackTrace();
		}
		catch (BrokenBarrierException e) {
			e.printStackTrace();
		}
		//## THREADS SYNCED ##
		
		
		this.gameOfLife();
		
		
		//## SYNC THREAD BARRIER ##
		try{
			barrier.await();
		}
		catch (InterruptedException e) {
			e.printStackTrace();
		}
		catch (BrokenBarrierException e) {
			e.printStackTrace();
		}
		//## THREADS SYNCED ##
				
		
		thread_end = System.currentTimeMillis();
		
    }
}
