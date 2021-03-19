package ChainOfResposibility;

public abstract class Processador {
	protected Processador prox;
	
	public Processador(Processador prox) {
		this.prox = prox;
	}
	
	public abstract String verify(String x);
	
}
