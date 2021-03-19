package bridge2;
import java.util.LinkedList;

public class FIFO implements List {
	
	LinkedList<Object> l = new LinkedList<Object>();
	
	public FIFO() {
	}
	
	public void enqueue(Object o) {
		l.add(o);
	}
	public Object dequeue() {
		return l.removeFirst();
	}
	public int size() {
		return l.size();
	}
}
