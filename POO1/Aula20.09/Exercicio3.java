package Aula2909;

import java.util.Scanner;

public class Exercicio3 {
	private String frase;

	public Exercicio3(String frase) {
		this.frase = frase;
	}

	public String getFrase() {
		return frase;
	}

	public void setFrase(String frase) {
		this.frase = frase;
	}

	//03
	public void lowUp(){
		System.out.println(getFrase().toUpperCase());
	}
	
	public void upLow(){
		System.out.println(getFrase().toLowerCase());
	}
	
	public static void main(String[] args){
		Scanner l1 = new Scanner(System.in);

		String fraseMain03 = l1.nextLine();
		Exercicio3 s3 = new Exercicio3(fraseMain03);
		s3.upLow();
		s3.lowUp();

		l1.close();
	}
}