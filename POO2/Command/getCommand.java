package banco;

import java.util.HashMap;

public class getCommand implements Command{
	private HashMap banco;
	
	public getCommand(Object bd) {
		banco = (HashMap) bd;	
	}
	
	public Object execute(Object argu) {
		System.out.println("Pessoa: "+((Pessoa)banco.get((int) argu)).getNome());
		return this.banco;
	}
}
