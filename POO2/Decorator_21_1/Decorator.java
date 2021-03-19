package Decorator;

public abstract class Decorator implements Componente {
	protected Componente c;
	
	public Decorator(Componente c) {
		this.c=c;
	}
	
	public String getString() {
		return c.getString();
	}
	
	public void op() {
		this.c.op();
	}
	
	public void setString(String x) {
		return;
	}
}
