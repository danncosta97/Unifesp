package Ex01;

public class Erro {
	public static void main(String[] args){
		try{
			throw new Exception ("Dados Incorretos");
		}
		catch(Exception erro){
			System.out.println("Erro: "+erro.getMessage());
		}
		finally{
			System.out.println("passou");
		}
	}
}
