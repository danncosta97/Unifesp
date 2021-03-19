package AppGUI;

public class Produto {
	private String nome;
	private String id;
	private double preco;
	
	public Produto() {
		this.nome = null;
		this.id = null;
		this.preco = 0;
	}
	
	public Produto Create(String nome,String id,double preco) {
		Produto Pro = new Produto();
		Pro.setId(id);
		Pro.setNome(nome);
		Pro.setPreco(preco);
		
		return Pro;
	}


	public void setNome(String nome) {
		this.nome = nome;
	}

	public void setId(String id) {
		this.id = id;
	}

	public double getPreco() {
		return preco;
	}
	
	public String getId() {
		return id;
	}

	public void setPreco(double preco) {
		this.preco = preco;
	}
}
