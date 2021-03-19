package Aula2909;

import java.util.Scanner;

public class Exercicio4 {
	private String frase;

	public Exercicio4(String frase) {
		this.frase = frase;
	}

	public String getFrase() {
		return frase;
	}

	public void setFrase(String frase) {
		this.frase = frase;
	}
	
	//04
	public void printSub(){
		int x = this.getFrase().length();
		
		for(int i=0;i<x+1;i++){
			System.out.println(this.getFrase().substring(0, i));
		}
		
		for(int k=x-1;k>=0;k--){
			System.out.println(this.getFrase().substring(0, k));
		}
	}
	
	public static void main(String[] args){
		Scanner l1 = new Scanner(System.in);

		//04
		String fraseMain04 = l1.nextLine();
		Exercicio4 s4 = new Exercicio4(fraseMain04);
		s4.printSub();
		l1.close();
	}
}