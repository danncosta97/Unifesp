package FactoryMethod;

public class TrEquilatero implements Figura{
	double b,h;
	
	TrEquilatero(double b, double h){
		this.b=b;
		this.h=h;
	}
	@Override
	public double area() {
		return ((b*h)/2);
	}

}
