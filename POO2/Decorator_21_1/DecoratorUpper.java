package Decorator;

public class DecoratorUpper extends Decorator{

	public DecoratorUpper(Componente c) {
		super(c);
	}
	
	public void op() {
		this.c.setString((this.c.getString()).toUpperCase());
	}
}
