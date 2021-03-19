package State_17_1;

public class DoorOpen implements Door_State{

	public Door_State click() {
		System.out.println("Fechando a porta");
		return new DoorClosing();
	}
	
}
