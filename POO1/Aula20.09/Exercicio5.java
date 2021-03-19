package Aula2909;
import java.util.Scanner;

public class Exercicio5 {
	private String frase;

	public Exercicio5(String frase) {
		this.frase = frase;
	}

	public String getFrase() {
		return frase;
	}

	public void setFrase(String frase) {
		this.frase = frase;
	}
	
	public void troca(){
		Scanner l1 = new Scanner(System.in);
		
		String x = l1.nextLine();

		String y = l1.nextLine();
		frase = frase.replace(x, y);
		
		l1.close();
	}
	
	public static void main(String[] args){
		Scanner l1 = new Scanner(System.in);
		String x = l1.nextLine();
		
		Exercicio5 frase = new Exercicio5(x);
		
		frase.troca();
		System.out.println(frase.getFrase());
		
		l1.close();
	}
}
