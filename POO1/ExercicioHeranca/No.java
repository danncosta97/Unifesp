package ExercicioHeranca;

public class No {

	    private Object dado;
	    private No anterior;
	    private No proximo;


	    public No(Object elemento, No anterior, No proximo) {
	        this.dado = elemento;
	        this.anterior = anterior;
	        this.proximo = proximo;

	    }

	    public Object getDado() {
	        return dado;
	    }
	    public void setDado(Object dado) {
	        this.dado = dado;
	    }
	    public No getAnterior(){
	        return anterior;
	    }
	    public void setAnterior(No anterior){
	        this.anterior = anterior;
	    }
	    public No getProximo() {
	        return proximo;
	    }
	    public void setProximo(No proximo) {
	        this.proximo = proximo;
	    }
}
