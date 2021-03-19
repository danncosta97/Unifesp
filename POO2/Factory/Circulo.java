package FactoryMethod;

public class Circulo implements Figura{
	double r;
	
	Circulo(double r){
		this.r=r;
	}
	
	@Override
	public double area() {
		return (2*Math.PI*r);
	}

}
