package banco;

import java.util.HashMap;

public class delCommand implements Command{
	private HashMap banco;
	
	public delCommand(Object bd) {
		banco = (HashMap) bd;	
	}
	
	public Object execute(Object argu) {
		int id = (int) argu;
		banco.remove(id);
		return this.banco;
	}
}
