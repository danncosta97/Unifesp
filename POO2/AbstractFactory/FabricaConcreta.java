package AbstractFactory;

public class FabricaConcreta implements FabricaFigura {

	@Override
	public Ponto criaPonto(double x, double y) {
		return new Ponto(x,y);
	}

	@Override
	public Circulo criaCirculo(Ponto p, double r) {
		return new Circulo(p,r);
	}

	@Override
	public Retangulo criaRetangulo(Ponto p, Ponto q) {
		return new Retangulo(p,q);
	}

	@Override
	public Triangulo criaTriangulo(Ponto p, Ponto q, Ponto s) {
		return new Triangulo(p,q,s);
	}

}
