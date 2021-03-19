package Ex1;

public class gerarHTML implements Visitante{
	public gerarHTML() {
		
	}
	public Object visitar(Planilha p) {
		p.gerarHTML();
		return null;
	}
	public Object visitar(Texto t) {
		t.gerarHTML();
		return null;
	}
	public Object visitar(Grafico g) {
		g.gerarHTML();
		return null;
	}
}
