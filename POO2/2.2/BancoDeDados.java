package AppGUI;
import java.util.Iterator;
import java.util.LinkedList;

public class BancoDeDados {
	private LinkedList<Cliente> c;
	private LinkedList<Produto> p;
	
	public Cliente SelectCliente(String id) {
		Cliente cli;
		Iterator<Cliente> lista = c.iterator();
		do {
			cli = lista.next();
		}while(cli.getId() != id);
		return cli;
	}
	
	public Produto SelectProduto(String id) {
		Produto pro;
		Iterator<Produto> lista = p.iterator();
		do {
			pro = lista.next();
		}while(pro.getId() != id);
		return pro;
	}
	
	public void ProcessarPagamento(Cliente c,double valor) {
		
	}
}
