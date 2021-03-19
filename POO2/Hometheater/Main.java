package Hometheater;

public class Main {

	public static void main(String[] args) {
		Hometheater home = new Hometheater();
		
		System.out.println(home.status());
		
		home.mudarAmplificador(50);
		home.mudarLuzAmb(0.5f);
		home.mudarVolume(80);
		home.ligarTela(true);
		home.pipocar(true);
		home.colocarFilme("Pantera Negra");
		
		System.out.println("\n\n"+home.status());

	}

}
