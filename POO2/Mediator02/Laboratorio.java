package Mediator2;

public class Laboratorio extends Colaborador{
	String nome;
	Mediator mediator;
		
	public Laboratorio(String nome) {
		this.nome = nome;
	}
	
	public void setMediator(Mediator m) {
		this.mediator=m;
	}

	@Override
	public void receiveMessage(String s) {
		System.out.println("(Send to "+this.nome+")"+s);
	}

	@Override
	public void updateTemperature(Float t) {
		return;
	}

	@Override
	public void updateRGB() {
		return;
	}
}