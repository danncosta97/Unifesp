public class MainGameOfLife {
	
	public static long start = 0;	//start timer for program
	public static long end = 0;	//start timer for program
	
	public static void main(String[] args) {
		
		System.out.printf("System Specs");
		System.out.printf("\nProcessor: Intel Core i3-8100 (6 MB Cache / 4 Cores / 4 Threads)");
		System.out.printf("\nRAM: 16 GB / 2400 MHz\n");
		System.out.printf("OS: Ubuntu 18.04\n\n");
		
		start = System.currentTimeMillis();
         
        GameOfLife r = new GameOfLife();
        
        Thread[] threads = new Thread[GameOfLife.threadAmount];
       
        for (int i = 0; i < GameOfLife.threadAmount; i++) {
            threads[i] = new Thread(r);
            threads[i].start();
        }
        
        for (int i = 0; i < GameOfLife.threadAmount; i++) {
            try {
				threads[i].join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        }
        
        System.out.println("\n\nThreads execution time: "+(long)(GameOfLife.thread_end - GameOfLife.thread_start)
        		+" ms (THREADS: "+GameOfLife.threadAmount+")");
        end = System.currentTimeMillis();
        System.out.println("Total execution time: "+(long)(end-start)+" ms\n");
        
    }
}
