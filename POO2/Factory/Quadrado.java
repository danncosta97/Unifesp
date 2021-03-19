package FactoryMethod;

public class Quadrado implements Figura{
	double l;
	
	Quadrado(double l){
		this.l=l;
	}
	
	public double area() {
		return l*l;
	}
}
