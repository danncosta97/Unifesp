package AbstractFactory;

public class Circulo implements Figuras{
	Ponto p;
	double r;
	
	Circulo (Ponto p, double r){
		this.p=p;this.r=r;
	}

	@Override
	public void info() {
		System.out.println("(Circulo)\nPonto\nx:"+this.p.x+" y:"+this.p.y+"\nRaio\nr:"+this.r);
	}
}
