package bridge1;

public class Main {
	public static void main(String[] args) {
		Queue q = new Queue();
		q.enqueue("1");q.enqueue("12");q.enqueue("13");
		while(q.isEmpty()==false) {
			System.out.println(q.dequeue());
		}
	}
}
