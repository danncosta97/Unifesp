package banco;

import java.util.HashMap;

public class AllCommand implements Command {
	private HashMap banco;
	
	public AllCommand(Object bd) {
		banco = (HashMap) bd;	
	}
	
	public Object execute(Object argu) {
		System.out.println("Dados do banco:\n");
		int i=0,x=0;
		while(i<banco.size()) {
			if(banco.containsKey(x)) {
				System.out.println( ((Pessoa)banco.get(x)).getNome() );
				i++;
			}
			x++;
		}
		
		return this.banco;
	}
}
