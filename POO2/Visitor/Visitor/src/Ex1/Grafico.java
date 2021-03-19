package Ex1;

public class Grafico implements Documento{
	public Object aceitar(Visitante v) {
		return v.visitar(this);
	}
	
	public void gerarHTML() {
		System.out.println("Gerando HTML do Grafico!");
	}
	
	public void gerarXML() {
		System.out.println("Gerando XML do Grafico!");
	}
	
	
	public void gerarTexto() {
		System.out.println("Gerando Texto do Grafico!");
	}
	
	public String toString() {
		return " Gráfico ";
	}
}

