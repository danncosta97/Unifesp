package bridge1;
import java.awt.List;
import java.util.LinkedList;



public class Queue {
	
	LinkedList l = new LinkedList();

	public Queue() {
	}

	public Object dequeue(){
		return this.l.removeFirst();
	}
	
	public void enqueue(Object o) {
		l.add(o);
	}
	
	public boolean isEmpty() {
		if (l.size()==0) {
			return true;
		}
		return false;
	}
	
	public int size() {
		return l.size();
	}
}
