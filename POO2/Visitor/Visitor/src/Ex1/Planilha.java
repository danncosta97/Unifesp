package Ex1;

public class Planilha implements Documento{
	public Object aceitar(Visitante v) {
		return v.visitar(this);
	}
	
	public void gerarHTML() {
		System.out.println("Gerando HTML da Planilha!");
	}
	
	public void gerarTexto() {
		System.out.println("Gerando Texto da Planilha!");
	}
	
	public void gerarXML() {
		System.out.println("Gerando XML da Planilha!");
	}
	
	
	public String toString() {
		return " Planilha ";
	}
}
