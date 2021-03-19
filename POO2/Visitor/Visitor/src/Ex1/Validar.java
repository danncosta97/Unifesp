package Ex1;

public class Validar implements Visitante{
	public Object visitar(Planilha p) {
		return new Boolean(true);
	}
	public Object visitar(Texto t) {
		return new Boolean(true);
	}
	public Object visitar(Grafico g) {
		return new Boolean(true);
	}
}
