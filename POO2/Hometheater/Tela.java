package Hometheater;

public class Tela {
	private boolean telaProjecao;
	private String dvdPlayer;
	private float luzAmbiente;
	private float brilhoTela;

	public float getBrilhoTela() {
		return brilhoTela;
	}

	public void setBrilhoTela(float brilhoTela) {
		this.brilhoTela = brilhoTela;
	}

	public Tela() {
		telaProjecao = false;
		dvdPlayer = "Sem filme";
		luzAmbiente = 0.0f;
	}

	public boolean isTelaProjecao() {
		return telaProjecao;
	}
	public void setTelaProjecao(boolean telaProjecao) {
		this.telaProjecao = telaProjecao;
	}
	public String isDvdPlayer() {
		return dvdPlayer;
	}
	public void setDvdPlayer(String dvdPlayer) {
		this.dvdPlayer = dvdPlayer;
	}
	public float getLuzAmbiente() {
		return luzAmbiente;
	}
	public void setLuzAmbiente(float luzAmbiente) {
		if(luzAmbiente < 0.2) {
			this.luzAmbiente = luzAmbiente;
			setBrilhoTela(0.2f);
		}
		else{
			this.luzAmbiente = luzAmbiente;
			setBrilhoTela(luzAmbiente);
		}
	}
}
