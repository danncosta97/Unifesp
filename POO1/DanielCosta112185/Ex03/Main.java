package Ex03;

public class Main {
	public static void main(String[] args){

		try{
			Aleatoria test = new Aleatoria();
			test.testa();
		}catch(Erro x){
			System.out.println("Erro: "+x.getMessage());
		}finally{
			System.out.println("passou");
		}
	}
}
