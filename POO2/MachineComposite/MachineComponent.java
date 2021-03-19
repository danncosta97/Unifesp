
public abstract class MachineComponent {
	public String name;
	
	public abstract int getMachineCount();
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
}