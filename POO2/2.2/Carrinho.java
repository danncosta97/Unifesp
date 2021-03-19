package AppGUI;

public class Carrinho {
	private double Total;
	private Produto[] p;
	public static int cont;
	
	public Carrinho() {
		cont = 0;
		this.Total = 0;
	}
	
	public Carrinho Create() {
		Carrinho Car = new Carrinho();
		return Car;
	}
	
	public void Adicionar(Produto p) {
		this.p[cont] = p;
		cont++;
	}
	
	public double getTotal() {
		return this.Total;
	}
	
}
