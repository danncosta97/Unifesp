package Mediator2;

public abstract class Colaborador {
	
	protected Mediator m;
	
	public void setMediator(Mediator m) {
		this.m = m;
	}
	
	public abstract void updateTemperature(Float t);
	
	public abstract void updateRGB();
	
	public abstract void receiveMessage(String s);
}
