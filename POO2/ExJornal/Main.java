package Ex32;

public class Main {
	
	public static void main(String args[]) {
		
		Publicacao Jornal = new Publicacao();
		Artigo artNova = new Artigo();
		Artigo artNewYork = new Artigo();
		Publicacao Caderno = new Publicacao();
		Publicacao Revista = new Publicacao();
		
		Artigo artJersey = new Artigo();
		
		Jornal.addArt(artNova);
		Jornal.addArt(Caderno);
		Caderno.addArt(artNewYork);
		Caderno.addArt(Revista);
		Revista.addArt(artJersey);
	}

}
