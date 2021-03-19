package FactoryMethod;

public abstract class Criador {	
	Figura f;
	
	abstract Figura getFigura();
	
	void op() {
		f = getFigura();
	}
}
