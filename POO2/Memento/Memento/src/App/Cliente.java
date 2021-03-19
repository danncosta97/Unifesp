package App;

public class Cliente {
	public static void main(String[] args) {
	    Texto texto = new Texto();
	    texto.escreverTexto("Brasil vai ser campeão\n");
	    texto.escreverTexto("Alemanha 7x1 Brasil\n");
	    texto.escreverTexto(" 'eu so queria dar alegria para o meu povo' \n");
	    texto.mostrarTexto();
	    texto.desfazerEscrita();
	    texto.mostrarTexto();
	    texto.desfazerEscrita();
	    texto.mostrarTexto();
	    texto.desfazerEscrita();
	    texto.mostrarTexto();
	}

}
