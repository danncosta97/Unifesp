package Ex03;

public class Erro extends Exception{
	private String s;
	
	public Erro(String s){
		this.s = s;
	}
	
	public String getMessage(){
		return this.s;
	}
}
