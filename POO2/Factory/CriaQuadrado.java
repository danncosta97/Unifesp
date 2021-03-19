package FactoryMethod;

public class CriaQuadrado extends Criador{

	@Override
	Figura getFigura() {
		return new Quadrado(4);
	}

}
