package Exercicios;

public class main {
	
	public static void main (String[] args){
		Mortal m1 = new Mortal();
		System.out.println(m1);
		m1.mata();
		System.out.println(m1);
		System.out.println();
		
		Gato g1 = new Gato();
		System.out.println(g1);
		g1.mata();
		System.out.println(g1);
		g1.mata();
		System.out.println(g1);
		g1.mata();
		System.out.println(g1);
		g1.mata();
		System.out.println(g1);
		g1.mata();
		System.out.println(g1);
		g1.mata();
		System.out.println(g1);
		g1.mata();
		
		System.out.println();
		Ramo r1 = new Ramo();
		Ramo r2 = new Ramo();
		Ramo r3 = new Ramo();
		r1.setGalhoEsq(r2);
		r2.setGalhoDir(r3);
		System.out.println(r1);
		r1.mata();
		System.out.println(r1);		
	}
}
