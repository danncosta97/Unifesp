package Flyweight;

import java.util.Random;

public class Main {
	public static void main(String[] args) {
		FlyweightFactory fab = new FlyweightFactory();
		Random gerador = new Random();
		
		for(int i=0;i<10;i++) {
			for(int j=0;j<10;j++) {
				Flyweight fly = fab.getFly(gerador.nextInt(10));
				fly.operacao();
			}
			System.out.println();
		}

	}
}
