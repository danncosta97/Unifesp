package ExercicioHeranca;

public class Lista {
	
	private Object tamanho;
	private No primeiro;
	private No ultimo;
	
	public Lista (){
		this.tamanho = 0;
		this.primeiro = null;
		this.ultimo = null;
	}

	public Object getTamanho() {
		return tamanho;
	}

	public void setTamanho(Object tamanho) {
		this.tamanho = tamanho;
	}

	public No getPrimeiro() {
		return primeiro;
	}

	public void setPrimeiro(No primeiro) {
		this.primeiro = primeiro;
	}

	public No getUltimo() {
		return ultimo;
	}

	public void setUltimo(No ultimo) {
		this.ultimo = ultimo;
	}
	
	public int listaVazia(){
		if(getTamanho() == (Object) 0){
			return 1;
		}
		else return 0;
	}
	
	public void insereFim(No novo){
		novo.setAnterior(getUltimo());
		getUltimo().setProximo(novo);
		setUltimo(novo);
	}
	
	public void removeFim(){
		setUltimo(getUltimo().getAnterior());
		getUltimo().setProximo(null);
	}
	
}
