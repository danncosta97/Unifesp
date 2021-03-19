package Body;

public class EmpresaBuild implements Construtor{

	protected Empresa emp;
	protected Pessoa pes;
	
	public EmpresaBuild() {
		Empresa emp = new Empresa();
	}
	
	public void lerNome(String nome) {
		emp.nome =nome;
	}
	
	public void lerIdentidade(int ident) {
		emp.identidade = ident;
	}
	
	public Pessoa pessoaDona(String nome,int iden) {
		PessoaBuild pb = new PessoaBuild();
		pb.lerIdentidade(iden);
		pb.lerNome(nome);
		pes = pb.getPessoa();
		return pes;
	}
	
	public Empresa getEmpresa() {
		return this.emp;
	}
}
