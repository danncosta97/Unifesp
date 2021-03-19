package AbstractFactory;

public class Triangulo implements Figuras{
	Ponto p,q,s;
	
	Triangulo (Ponto p, Ponto q,Ponto s){
		this.p=p;this.q=q;this.s=s;
	}

	@Override
	public void info() {
		System.out.println("(Triangulo)\nPonto 1\nx1:"+this.p.x+" y1:"+this.p.y+"\nPonto 2\nx2:"+this.q.x+" y2:"+this.q.y+"\nPonto 3\nx3:"+this.s.x+" y3:"+this.s.y);
	}
}
