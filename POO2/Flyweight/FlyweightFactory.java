package Flyweight;

import java.util.HashMap;
import java.util.Map;

public class FlyweightFactory {
	Map<Integer, Flyweight> mapa = new HashMap<Integer,Flyweight>();
	
	public FlyweightFactory() {
		
	}
	
	public Flyweight getFly(int x) {
		if(mapa.containsKey(x)) {
			return (Flyweight) mapa.get(x); 
		}
		else{
			Flyweight fly = new FlyweightConcreto(x);
			mapa.put(x, fly);
			return fly;
		}
	}
}
