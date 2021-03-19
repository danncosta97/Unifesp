package App;

public class Memento {
	protected String estadoTexto;
	 
    public Memento(String texto) {
        estadoTexto = texto;
    }
 
    public String getTextoSalvo() {
        return estadoTexto;
    }
}
