package State_17_1;

public class DoorClosing implements Door_State{
	public Door_State click() {
		System.out.println("Abrindo a porta");
		return new DoorClosing();
	}
}
