package Observer;
import java.util.*;

public class Observable {
	
	Long obs_id;
	ArrayList<Object> observers = new ArrayList<Object>();
	
	public Long getObservableId() {
		return obs_id;
	}
	
	public void register(Observer o) {
		observers.add(o);
	}
	
	public void delete(Observer o) {
		Iterator<Object> it = observers.iterator();
		
		while(it.hasNext()) {
			Observer it_obs = (Observer) it.next();
			if (it_obs == o) {
				it.remove();
			}
		}
	}
	
	public void notificar(String args) {
		Iterator<Object> it = observers.iterator();
		
		while(it.hasNext()) {
			Observer it_obs = (Observer) it.next();
			it_obs.update(this, args);
		}
	}
	
	
}
