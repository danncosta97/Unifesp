package AppGUI;

public class Facade {
	BancoDeDados banco = new BancoDeDados();
	
	public void Registrar(String nome, String id) {
		//Add cliente no banco
	}
	
	public void Comprar(String idp,String idc) {
		//Add produto no banco
	}
	
	public void fecharCompra(String id) {
		Cliente c = banco.SelectCliente(id);
		double valor = c.getCarrinho().getTotal();
		banco.ProcessarPagamento(c, valor);
	}
}
