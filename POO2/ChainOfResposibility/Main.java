package ChainOfResposibility;

public class Main {
	public static void main(String args[]) {
		Processador p3 = new ProcessaDot(null);
		Processador p2 = new ProcessaSpace(p3);
		Processador p1 = new ProcessaA(p2);
		
		System.out.println(p1.verify("Contagem de 'a(s)', espaços e pontos em uma frase usando o padrao de projeto Chain Of Resposibility"));
	}
}
