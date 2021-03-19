package Body;

public class Diretor {
	protected Construtor construtor;
	
	public Diretor(String nomeE,int iden,String nomeP) {
		this.construtor = new EmpresaBuild();
	}
	
	public Diretor(String nome,int iden) {
		this.construtor = new PessoaBuild();
	}
	
	
}
