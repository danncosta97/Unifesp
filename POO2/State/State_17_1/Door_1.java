package State_17_1;

import java.util.Objects;

public class Door_1{
		
	protected Door_State state;
	
	public Door_1() {
		state = new DoorClosed();
		
	}
	
	public void setState(Door_State s) {
		this.state=s;
	}
		
	public void click() {
		//portas demoram 1s para abrir/fechar
		this.state = this.state.click();
		
		String s = this.state.getClass().getName();
		s = s.substring(s.indexOf('.')+1);
		
		if(Objects.equals(s, "DoorOpening")) {
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			
			this.setState(new DoorOpen());
		}
		if(Objects.equals(s, "DoorClosing")) {
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			
			this.setState(new DoorClosed());
		}
	}
	
	public void status() {
		String s = this.state.getClass().getName();
		s = s.substring(s.indexOf('.')+1);
		if(Objects.equals(s, "DoorOpen")) 
			System.out.println("Porta Aberta");
		else if(Objects.equals(s, "DoorClosed")) 
			System.out.println("Porta Fechada");
		else if(Objects.equals(s, "DoorOpening"))
			System.out.println("Abrindo a porta");
		else if(Objects.equals(s, "DoorClosing"))
			System.out.println("Fechando a porta");		
	}
	
}
