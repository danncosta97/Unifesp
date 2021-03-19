package Prototype;

public class CriaTrEquilatero extends Criador{

	@Override
	Figura getFigura() {
		return new TrEquilatero(5,3);
	}

}
