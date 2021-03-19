package Prototype;

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

	public Figura clone(Object o) {
		return new TrEquilatero(((TrEquilatero)o).b,((TrEquilatero)o).h);
	}
}
