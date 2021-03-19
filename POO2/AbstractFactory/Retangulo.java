package AbstractFactory;

public class Retangulo implements Figuras{
	Ponto p,q;
	
	Retangulo (Ponto p, Ponto q){
		this.p=p;this.q=q;
	}

	@Override
	public void info() {
		System.out.println("(Retangulo)\nPonto 1\nx1:"+this.p.x+" y1:"+this.p.y+"\nPonto 2\nx2:"+this.q.x+" y2:"+this.q.y);
	}
}
