package Ex32;


import java.util.*;

public class Publicacao extends Componente{
	protected List<Componente> art = new ArrayList<Componente>();
	private String nome;
	
	public Publicacao() {
		this.nome = null;
	}
	
	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}

	public void addArt(Componente comp) {
		art.add(comp);
	}
}
