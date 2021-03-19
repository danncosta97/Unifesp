package Ex04;

public class Main {
	public static void main(String[] args){

		try{
			Exception erro = null;
			erro.getMessage();
		}catch(NullPointerException error){
			System.out.println("Erro: "+ error.getMessage());
		}finally{
			System.out.println("passou");
		}
	}
}
