package Mediator2;

import java.util.ArrayList;
import java.util.Iterator;

public class Messenger implements Mediator{
	ArrayList<Colaborador> conected = new ArrayList<Colaborador>();
	
	public void addColaborador(Colaborador c) {
		this.conected.add(c);
		c.setMediator(this);
	}

	public void send(String s, Colaborador c) {
		Iterator<Colaborador> it = this.conected.iterator();
		while(it.hasNext()) {
			Colaborador c1 = it.next();
			if(c1 == c) {
				Iterator<Colaborador> it2 = this.conected.iterator();
				while(it2.hasNext()) {
					Colaborador c2 = it2.next();
					if(!(c2 instanceof Sensor)) {
						c2.receiveMessage(s);
					}
				}
			}
		}
		System.out.println("=======================================================================================");
	}
}
