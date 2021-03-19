package Prototype;

public class CriaQuadrado extends Criador{

	Figura getFigura() {
		return new Quadrado(4);
	}

}
