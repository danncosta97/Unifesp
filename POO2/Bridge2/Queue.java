package bridge2;

public abstract class Queue {
	protected List l;
	
	public void enqueue(Object o) {
		l.enqueue(o);
	}
	public Object dequeue() {
		return l.dequeue();
	}
	public boolean isEmpty() {
		if(l.size() == 0)
			return true;
		return false;
	}
	
	public int size() {
		return l.size();
	}
}
