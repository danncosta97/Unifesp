package Exercicios;

public class Figura {
	private double area;

	public Figura() {
		this.area = 0;
	}

	public double getArea() {
		return area;
	}

	public void setArea(double area) {
		this.area = area;
	}
	
	public String toString(){
		return "Area: " + getArea();
	}
}
