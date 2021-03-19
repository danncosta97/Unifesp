package Body;

public class PessoaBuild implements Construtor{
	
	protected Pessoa pes;
	
	public PessoaBuild() {
		Pessoa pes = new Pessoa();
	}
	
	public void lerNome(String nome) {
		pes.nome = nome;
	}
	
	public void lerIdentidade(int iden) {
		pes.identidade = iden;
	}
	
	public Pessoa getPessoa() {
		return this.pes;
	}

}
