package AbstractFactory;

public interface FabricaFigura {
	Ponto criaPonto(double x, double y);
	Circulo criaCirculo(Ponto p, double r);
	Retangulo criaRetangulo(Ponto p, Ponto q);
	Triangulo criaTriangulo(Ponto p, Ponto q, Ponto s);
}
