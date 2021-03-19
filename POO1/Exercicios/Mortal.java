package Exercicios;

public class Mortal {
	
	private boolean vivo;
	
	public Mortal(){
		this.vivo = true;
	}
	
	public boolean isVivo(){
		return vivo;
	}
	
	public void setVivo(boolean x){
		this.vivo = x;
	}
	
	public void mata(){
		boolean x = false;
		setVivo(x);
	}
	
	public String toString(){
		return "Estado: " + this.isVivo();
	}
}