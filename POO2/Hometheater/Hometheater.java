package Hometheater;

public class Hometheater {
	private Maquina maq;
	private Tela tel;
	private Som som;
	
	public Hometheater() {
		maq = new Maquina();
		tel = new Tela();
		som = new Som();
	}
	
	public String status() {
		return "Fazendo pipoca: "+maq.isFazendoPipoca()+"\nPegando Refri: "+maq.isFazendoRefri()+
				"\nEstado Tela: "+tel.isTelaProjecao()+"\nFilme: "+tel.isDvdPlayer()+
				"\nLuz Ambiente em: "+tel.getLuzAmbiente()+"\nBrilho Tela: "+tel.getBrilhoTela()+
				"\nVolume: "+som.getVolume()+"\nAmplificador: "+som.getAmplificador();
	}
	
	public void pipocar(boolean valor) {
		maq.setFazendoPipoca(valor);
	}
	
	public void pegarRefri(boolean valor) {
		maq.setFazendoRefri(valor);
	}
	
	public void ligarTela(boolean valor) {
		tel.setTelaProjecao(valor);
	}
	
	public void mudarLuzAmb(float valor) {
		tel.setLuzAmbiente(valor);
	}
	
	public void colocarFilme(String filme) {
		tel.setDvdPlayer(filme);
	}
	
	public void mudarVolume(int vol) {
		som.setVolume(vol);
	}
	
	public void mudarAmplificador(int amp) {
		som.setAmplificador(amp);
	}
	
	
	public Maquina getMaq() {
		return maq;
	}
	
	public void setMaq(Maquina maq) {
		this.maq = maq;
	}
	public Tela getTel() {
		return tel;
	}
	public void setTel(Tela tel) {
		this.tel = tel;
	}
	public Som getSom() {
		return som;
	}
	public void setSom(Som som) {
		this.som = som;
	}
}
