package aula0411;

import java.util.Scanner;

public class Main {
	public static void main(String[] args) throws InterruptedException{
		Scanner scanner = new Scanner(System.in);
		int inicio = scanner.nextInt();
		int fim = scanner.nextInt();
		
		
		int qtd = scanner.nextInt();
		Thread[] p = new Thread[qtd];
		
		int k = ((fim-inicio)/qtd); //intervalo
		
		int j=inicio;
		
		for(int i=0;i<qtd;i++){
			p[i] = new Thread(new PrimoThread(j,k));
			p[i].start();
			j = k;
			k = k+k;
			
		}
		
		for(int i=0;i<qtd;i++){
			p[i].join();
		}
		
		System.out.println("Primos: "+ PrimoThread.getPrimoCont());
		scanner.close();
	}
}
