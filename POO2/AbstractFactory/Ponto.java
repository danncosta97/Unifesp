package AbstractFactory;

public class Ponto implements Figuras{
	
	double x,y;
	
	Ponto (double x, double y){
		this.x=x;this.y=y;
	}

	@Override
	public void info() {
		System.out.println("(Ponto)\nx:"+this.x+" y:"+this.y);
	}
}
