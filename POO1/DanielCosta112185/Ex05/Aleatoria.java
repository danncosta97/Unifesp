package Ex05;

public class Aleatoria {
	
	public Aleatoria(){
		
	}
	
	public void f()throws Exception{
		try{
			this.g();

		}catch(Erro x){
			System.out.println("Tratando g...");	
			throw new Exception("Erro f");
		}
	}
	
	public void g() throws Erro{
		throw new Erro("Dados Incorretos");
	}
}
