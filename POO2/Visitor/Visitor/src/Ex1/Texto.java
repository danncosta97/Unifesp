package Ex1;

public class Texto implements Documento{
	public Object aceitar(Visitante v) {
		return v.visitar(this);
	}
	
	public void gerarHTML() {
		System.out.println("Gerando HTML do Texto!");
	}
	
	public void gerarTexto() {
		System.out.println("Gerando Texto do Texto!");
	}
	
	public void gerarXML() {
		System.out.println("Gerando XML do Texto!");
	}
	
	public String toString() {
		return " Texto ";
	}
}
