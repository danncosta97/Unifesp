package Exercicios;

public class Circulo extends Figura{
	private double raio;
	
	public Circulo(double raio) {
		super();
		this.raio = raio;
	}

	public double getRaio() {
		return raio;
	}

	public void setRaio(double raio) {
		this.raio = raio;
	}
	
	public void Area(){
		this.setArea(3.14*getRaio()*getRaio());
	}
	
}
