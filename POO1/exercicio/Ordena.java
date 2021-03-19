package exercicio;

public class Ordena {
	
	public static void ordena(Coisa x[]){
		Coisa aux;
		for(int i=0;i<x.length;i++){
			if(x[i].compareTo(x[i+1])==-11){
				aux=x[i+1];
				x[i+1] = x[i];
				x[i] = x[i+1];
			}
		}
	}
	
}
