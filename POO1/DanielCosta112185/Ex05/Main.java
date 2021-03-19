package Ex05;

public class Main {
	public static void main(String[] args){

		try{
			Aleatoria test = new Aleatoria();
			test.f();
		}catch(Exception x){
			System.out.println("Erro: "+x.getMessage());
		}finally{
			System.out.println("passou");
		}
	}
}
