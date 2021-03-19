package Aula2909;
import java.util.Scanner;
public class Exercicio1 {
		private String frase;

		public Exercicio1(String frase) {
			this.frase = frase;
		}

		public String getFrase() {
			return frase;
		}

		public void setFrase(String frase) {
			this.frase = frase;
		}
		
		public int tamanho(){
			return this.getFrase().length();
		}
		
		
		public static void main(String[] args){
			Scanner l1 = new Scanner(System.in);
			
			String fraseMain01 = l1.nextLine();
			Exercicio1 s1 = new Exercicio1(fraseMain01);
			System.out.println(s1.tamanho());
			l1.close();
		}
}
