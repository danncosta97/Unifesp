package AppGUI;

public class Cliente {
	private String id;
	private String nome;
	private Carrinho c;
	
	public Cliente() {
		this.id = null;
		this.nome = null;
	}
	
	public Cliente Create(String id,String nome) {
		Cliente Cli = new Cliente();
		Cli.setId(id);
		Cli.setNome(nome);
		
		return Cli;
	}
	
	public void AdicionarCarrinho(Carrinho c) {
		this.c = c;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public Carrinho getCarrinho() {
		return this.c;
	}
	
	
}
