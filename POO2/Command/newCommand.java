package banco;

import java.util.HashMap;

public class newCommand implements Command{
	private HashMap banco;
	
	public newCommand(Object bd) {
		banco = (HashMap) bd;	
	}
	
	public Object execute(Object argu) {
		if(banco.isEmpty()) {
			Pessoa pes = new Pessoa();
			pes.setId(0);
			pes.setNome((String) argu);
			banco.put(0, pes);
		}else {
			Pessoa pes = new Pessoa();
			pes.setId(banco.size());
			pes.setNome((String) argu);
			banco.put(banco.size(), pes);
		}
		return this.banco;
	}
}
