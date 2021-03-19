
public class Main {
	public static void main(String args[]) {
		MachineComposite m = new MachineComposite();
		Machine ma = new Machine();
		ma.setName("peca1");	
		m.add(ma);
		
		Machine mb = new Machine();
		ma.setName("peca2");
		m.add(mb);
		
		Machine mc = new Machine();
		ma.setName("peca3");
		m.add(mc);

		System.out.println(m.getMachineCount());
	}
}
