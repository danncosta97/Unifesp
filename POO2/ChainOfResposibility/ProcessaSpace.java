package ChainOfResposibility;

public class ProcessaSpace extends Processador {
	
	public ProcessaSpace(Processador prox) {
		super(prox);
	}

	public String verify(String x){
		String y="";
		if(this.prox!=null) {
			y=prox.verify(x);
		}
		
		int cont=0;			    
	    for(int i=0;i<x.length();i++) {
	    	if(x.charAt(i)==' ') {
	    		cont++;
	    	}
	    }
	    
	    return cont+" espaço(s)\n"+y;
	}

}
