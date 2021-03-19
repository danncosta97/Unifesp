package App;

public class Retangulo implements Figura{
	private double ladoa;
	private double ladob;
	
	public Retangulo(double a,double b) {
		this.ladoa =  a;
		this.ladob =  b;
	}
	
	public double area() {
		
		double a = ladoa*ladob;
		return a;
	}

}
