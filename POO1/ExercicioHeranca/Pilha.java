package ExercicioHeranca;

public class Pilha extends Lista {
	
	public Pilha(){
		super();
	}
	
	public void empilha(No novoNo){
		super.insereFim(novoNo);
	}
	
	public void desempilha(){
		setUltimo(getUltimo().getAnterior());
		
	}
}
