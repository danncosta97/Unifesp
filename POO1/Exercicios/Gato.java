package Exercicios;

public class Gato extends Mortal{
	private int vidas;
	
	public Gato(){
		super();
		this.vidas = 6;
	}

	public int getVidas() {
		return vidas;
	}

	public void setVidas(int vidas) {
		this.vidas = vidas;
	}
	
	public void mata(){
		this.vidas--;
		if (vidas == 0){
			setVivo(false);
		}
	}
	
	public String toString(){
		return super.toString() + " Vidas: " + this.getVidas();
	}
}