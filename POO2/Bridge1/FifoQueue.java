package bridge1;
import java.awt.*;
import java.util.ArrayList;
import java.util.LinkedList;

public class FifoQueue extends Queue{

	 LinkedList l = new LinkedList();
	
	public FifoQueue() {
	}
	
	public LinkedList getFifoQueue(){
		return this.l;
	}
	
	public Object dequeue(){
		return getFifoQueue().removeFirst();
	}
	
	public void enqueue(Object o) {
		getFifoQueue().addLast(o);
	}
	
	public boolean isEmpty() {
		return getFifoQueue().isEmpty();
	}
	
	public int size() {
		return getFifoQueue().size();
	}
}
