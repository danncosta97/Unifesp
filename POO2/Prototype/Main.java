package Prototype;

public class Main {
	public static void main(String[] args) {
		Criador q =  new CriaQuadrado();
		Figura f = q.getFigura();
		System.out.println(f.area());
		Figura g = q.getFigura().clone(f);
		System.out.println(g.area());

		if(f.equals(g)) {
			System.out.println("Mesmo objeto");
		}
			else {
				System.out.println("Clone validado");
			}
		}
}
