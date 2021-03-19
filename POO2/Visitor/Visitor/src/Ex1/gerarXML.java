package Ex1;

public class gerarXML implements Visitante{
	public gerarXML() {
		
	}
	public Object visitar(Planilha p) {
		p.gerarXML();
		return null;
	}
	public Object visitar(Texto t) {
		t.gerarXML();
		return null;
	}
	public Object visitar(Grafico g) {
		g.gerarXML();
		return null;
	}
}
