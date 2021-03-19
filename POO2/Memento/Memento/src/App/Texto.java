package App;

public class Texto {
	   protected String texto;
	   TextoBackup caretaker;
	 
	    public Texto() {
	        caretaker = new TextoBackup();
	        texto = new String();
	    }
	 
	    public void escreverTexto(String novoTexto) {
	        caretaker.adicionarMemento(new Memento(texto));
	        texto += novoTexto;
	    }
	 
	    public void desfazerEscrita() {
	        texto = caretaker.getUltimoEstadoSalvo().getTextoSalvo();
	    }
	 
	    public void mostrarTexto() {
	        System.out.println(texto);
	    }
}
