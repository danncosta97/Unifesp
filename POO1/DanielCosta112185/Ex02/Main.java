package Ex02;

public class Main {
	public static void main(String[] args){

		try{
			throw new Erro("Dados errados");
		}catch(Erro ex){
			System.out.println("Erro: "+ex.getMessage());
		}
		finally{
			System.out.println("passou");
		}
	}
}
