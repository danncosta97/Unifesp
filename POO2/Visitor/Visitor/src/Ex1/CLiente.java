package Ex1;

public class CLiente {

	public static void main(String[] args) {
		Documento doc = new Texto();
		doc.aceitar(new gerarHTML());
		doc.aceitar(new gerarXML());
		if(((boolean)doc.aceitar(new Validar()))) {
			System.out.println(doc + " válido!");
		}
	}

}
