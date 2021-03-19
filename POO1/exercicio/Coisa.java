package exercicio;

public class Coisa implements Comparable{
	
	private int dado;
	
	public Coisa(int dado){
		this.dado = dado;
	}

	public int getDado() {
		return dado;
	}

	public void setDado(int dado) {
		this.dado = dado;
	}
	
	public int compareTo(Comparable x1){
		Coisa c1 = (Coisa) x1;
		
		if(this.dado > c1.getDado())
			return 1;
		if(this.dado < c1.getDado())
			return -1;
		return 0;
	}
}
