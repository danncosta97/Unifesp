package Decorator;

public class DecoratorTag extends Decorator{
	
	public DecoratorTag(Componente c) {
		super(c);
	}
	
	public void op() {
		this.c.setString("<b>"+this.getString()+"</b>");
	}
}
