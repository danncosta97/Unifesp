package bridge2;

public class Main{
	public static void main(String[] args) {
		ExtendQueue e = new ExtendQueue();

		e.enqueue("1");
		e.enqueue("2");
		e.enqueue("3");
		
		while(e.isEmpty()==false) {
			System.out.println(e.dequeue());
		}
	}
}
