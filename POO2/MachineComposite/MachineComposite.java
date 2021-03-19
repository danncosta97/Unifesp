import java.util.*;

public class MachineComposite extends MachineComponent {
	protected List components = new ArrayList();
	
	public void add(MachineComponent component) {
		components.add(component);
	}
	
	public int getMachineCount() {
		return components.size();
	}
}