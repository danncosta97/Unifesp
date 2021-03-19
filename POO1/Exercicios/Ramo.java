package Exercicios;

public class Ramo extends Mortal{
	private Ramo galhoEsq;
	private Ramo galhoDir;
	
	public Ramo(){
		super();
		this.galhoEsq = null;
		this.galhoDir = null;
	}

	public Ramo getGalhoEsq() {
		return galhoEsq;
	}

	public void setGalhoEsq(Ramo galhoEsquerdo) {
		galhoEsq = galhoEsquerdo;
	}

	public Ramo getGalhoDir() {
		return galhoDir;
	}

	public void setGalhoDir(Ramo galhoDireito) {
		galhoDir = galhoDireito;
	}
	
	public void mata(){
		if(getGalhoDir()!=null){
			setGalhoDir(null);
		}
		if(getGalhoEsq()!=null){
			setGalhoEsq(null);
		}
	}
	
	public String toString(){
		return super.toString() + "\n" + " Galho esquerdo: " + this.getGalhoEsq()
								+ "\n" + "Galho direito: " + this.getGalhoDir() + 
								"\n";
	}
	
}
