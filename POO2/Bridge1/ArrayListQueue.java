package bridge1;
import java.awt.List;
import java.util.ArrayList;
import java.util.LinkedList;

public class ArrayListQueue extends FifoQueue{
	
	ArrayList x = new ArrayList();
	
	public ArrayListQueue() {
	}
	
	public ArrayList getArrayList() {
		return this.x;
	}
	
	public Object dequeue() {
		return x.remove(0);
	}
	
	public void enqueue(Object o) {
		getArrayList().add(o);
	}
	
	public boolean isEmpty() {
		return getArrayList().isEmpty();
	}
	
	public int size() {
		return getArrayList().size(); 
	}

}
