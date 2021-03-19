package FactoryMethod;

public class Main {
	public static void main(String[] args) {
		Criador q =  new CriaQuadrado();
		Figura f = q.getFigura();
		System.out.println(f.area());
	}
}
