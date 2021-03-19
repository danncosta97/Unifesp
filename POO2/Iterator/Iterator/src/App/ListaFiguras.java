package App;

import java.util.ArrayList;

public class ListaFiguras implements IteratorInterface{
	protected ArrayList<Figura> lista;
    protected int contador;
	
	public ListaFiguras(ArrayList a) {
        this.lista = a;
        contador = 0;
	}
	
    public void first() {
        contador = 0;
    }
 
    public void next() {
        contador++;
    }
 
    public boolean isDone() {
        return contador == lista.size();
    }
 
    public Figura currentItem() {
        if (isDone()) {
            contador = lista.size() - 1;
        } else if (contador < 0) {
            contador = 0;
        }
        return lista.get(contador);
    }
}
