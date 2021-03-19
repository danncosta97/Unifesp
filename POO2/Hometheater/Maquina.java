package Hometheater;

public class Maquina {
	private boolean fazendoPipoca;
	private boolean fazendoRefri;
	
	public Maquina() {
		fazendoPipoca = false;
		fazendoRefri = false;
	}
	
	public boolean isFazendoPipoca() {
		return fazendoPipoca;
	}
	public void setFazendoPipoca(boolean fazendoPipoca) {
		this.fazendoPipoca = fazendoPipoca;
	}
	public boolean isFazendoRefri() {
		return fazendoRefri;
	}
	public void setFazendoRefri(boolean fazendoRefri) {
		this.fazendoRefri = fazendoRefri;
	}
	
	
	
}
