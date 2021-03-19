package AbstractFactory;

public class Main {
	public static void main(String[] args) {
		FabricaFigura f = new FabricaConcreta();
		Figuras p1 = f.criaPonto(4, 5);
		p1.info();
		Figuras p2 = f.criaPonto(10, 2);
		p2.info();
		Figuras c = f.criaRetangulo((Ponto)p1,(Ponto)p2);
		c.info();
	}
}
