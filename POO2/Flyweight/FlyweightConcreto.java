package Flyweight;

public class FlyweightConcreto implements Flyweight{
	
	private int key;
	
	public FlyweightConcreto(int x) {
		this.key=x;
	}
	public void operacao() {
		System.out.print(key);
	}
	
	public int getKey() {
		return this.key;
	}
}
