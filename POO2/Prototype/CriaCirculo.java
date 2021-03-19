package Prototype;

public class CriaCirculo extends Criador{

	@Override
	Figura getFigura() {
		return new Circulo(20);
	}

}
