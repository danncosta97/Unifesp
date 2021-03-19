package ExercicioHeranca;

public class Fila extends Lista {
	
	public Fila (){
		super();
	}
	
	public void insereNoFim(No novoNo){
		super.insereFim(novoNo);
	}
	
	public void removePrimeiro(){
		setPrimeiro(getPrimeiro().getProximo());
		getPrimeiro().setAnterior(null);
	}
	
}
