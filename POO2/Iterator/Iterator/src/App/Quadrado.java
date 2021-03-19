package App;

public class Quadrado implements Figura{
	private double lado;
	
	public Quadrado(double a) {
		this.lado =  a;
	}
	
	public double area() {
		
		double a = lado*lado;
		return a;
	}
}
