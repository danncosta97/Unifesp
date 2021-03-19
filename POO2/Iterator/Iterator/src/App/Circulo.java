package App;

public class Circulo implements Figura{
	private double raio;
	
	public Circulo(double a) {
		this.raio =  a;
		
	}
	
	public double area() {
		
		double a = 2*(3.14)*(raio*raio);
		return a;
	}

}
