package Decorator;

public class ComponenteConcreto implements Componente{
	protected String s;
	
	public ComponenteConcreto(String x) {
		this.s=x;
	}
	
	@Override
	public String getString() {
		return this.s;
	}

	public void setTexto(String x) {
		this.s = x;
	}
	
	@Override
	public void op() {
		return;
	}

	@Override
	public void setString(String s) {
		this.s=s;
	}
}
