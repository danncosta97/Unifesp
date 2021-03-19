package Decorator;

public class DecoratorReverse extends Decorator{
	public DecoratorReverse(Componente c) {
		super(c);
	}
	
	public void op() {
		StringBuffer buffer = new StringBuffer(c.getString());
        c.setString(buffer.reverse().toString());
	}
}
