package App;

import java.util.ArrayList;

public class Cliente {

	public static void main(String args[]) {
		ArrayList<Figura> lista = new <Figura>ArrayList();
		Figura c0 = new Circulo(2);
		Figura c1= new Circulo(8);
		
		Figura r0 = new Retangulo(3,5);
		Figura r1 = new Retangulo(7,1);
		
		Figura q0 = new Quadrado(4);
		Figura q1 = new Quadrado(9);
		
		
		lista.add(c0);
		lista.add(c1);
		lista.add(r0);
		lista.add(r1);
		lista.add(q0);
		lista.add(q1);
		
		ListaFiguras listaFig = new ListaFiguras(lista);
		listaFig.first();
		
		do {
			System.out.println(" "+listaFig.currentItem().area()+" ");
			listaFig.next();
			
		}while(listaFig.isDone()!=true);
	}
}
