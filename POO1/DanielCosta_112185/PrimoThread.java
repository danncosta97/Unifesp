package aula0411;

public class PrimoThread implements Runnable{
	private int start;
	private int end;
	private static int primoCont;
		
	public PrimoThread(int start, int end){
		this.start = start;
		this.end = end;
	}
	

	public static int getPrimoCont(){
		return primoCont;
	}
	
	  public void run() {

	        for (int i=this.start; i<this.end; i++) {

	        	int cont=0;
	        	for(int j=1; j<this.end;j++){
	        		if(i%j==0){
	        			cont++;
	        		}
	        	}

	        	if(cont==2){

	        		primoCont = primoCont+1;
	        	}
	        }
	   }
}
