package Aula2909;
import java.util.Scanner;

public class Exercicio6 {
	private String frase;

	public Exercicio6(String frase) {
		this.frase = frase;
	}

	public String getFrase() {
		return frase;
	}

	public void setFrase(String frase) {
		this.frase = frase;
	}
	
	public void indice(){
		Scanner l1 = new Scanner(System.in);
		
		String x = l1.nextLine();

		int y = frase.indexOf(x);
		System.out.println(y);
		
		l1.close();
	}
	
	public static void main(String[] args){
		Scanner l1 = new Scanner(System.in);
		String x = l1.nextLine();
		
		Exercicio6 frase = new Exercicio6(x);
		
		frase.indice();
		System.out.println(frase.getFrase());
		
		l1.close();
	}
}