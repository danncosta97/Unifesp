package Aula2909;

import java.util.Scanner;

public class Exercicio2 {
	private String frase;

	public Exercicio2(String frase) {
		this.frase = frase;
	}

	public String getFrase() {
		return frase;
	}

	public void setFrase(String frase) {
		this.frase = frase;
	}

	//02
	public void printCharAt(){
		int x = this.getFrase().length();
		
		for(int i=0;i<x;i++){
			for(int j=0;j<i+1;j++){
				System.out.printf("%c",this.getFrase().charAt(j));
			}
			System.out.printf("\n");
		}
		
		for(int k=x-1;k>=0;k--){
			for(int l=0;l<k;l++){
				System.out.printf("%c",this.getFrase().charAt(l));
			}
			System.out.printf("\n");
		}
	}
	
	public void upLow(){
		System.out.println(getFrase().toLowerCase());
	}

	
	public static void main(String[] args){
		Scanner l1 = new Scanner(System.in);

		//02
		String fraseMain02 = l1.nextLine();
		Exercicio2 s2 = new Exercicio2(fraseMain02);
		s2.printCharAt();

		l1.close();
	}
}