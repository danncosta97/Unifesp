package ChainOfResposibility;

public class ProcessaDot extends Processador{

	public ProcessaDot(Processador prox) {
		super(prox);
	}

	public String verify(String x){
		String y="";
		if(this.prox!=null) {
			y=prox.verify(x);
		}
		
		int cont=0;			    
	    for(int i=0;i<x.length();i++) {
	    	if(x.charAt(i)=='.') {
	    		cont++;
	    	}
	    }
	    
	    return cont+" ponto(s)\n"+y;
	}

}
