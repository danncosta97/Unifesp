package Prototype;

public class Quadrado implements Figura{
	double l;
	
	Quadrado(double l){
		this.l=l;
	}
	
	public double area() {
		return l*l;
	}
	
	public Figura clone(Object o) {
		return new Quadrado(((Quadrado)o).l);
	}
}
