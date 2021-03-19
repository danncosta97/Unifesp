package Prototype;

public class Circulo implements Figura{
	double r;
	
	Circulo(double r){
		this.r=r;
	}
	
	@Override
	public double area() {
		return (2*Math.PI*r);
	}

	public Figura clone(Object o) {
		return new Circulo(((Circulo)o).r);
	}

}
