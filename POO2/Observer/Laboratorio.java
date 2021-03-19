package Observer;

import java.util.*;

public class Laboratorio implements Observer{
	
	String nome;
	
	public Laboratorio(String nome) {
		this.nome = nome;
	}

	public void update(Observable o, String args) {
		
		Date date = new Date(System.currentTimeMillis());
		
		System.out.println("["+date.toString()+"] "+o.getObservableId()+" notificou "+args+" para "+nome+"!");
	}
}