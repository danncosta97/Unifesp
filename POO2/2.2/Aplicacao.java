package AppGUI;

public class Aplicacao {
	static Facade f = new Facade();
	
	public static void main(String args[]) {
		f.Registrar("Zé", "123");
		f.Comprar("223", "123");
		f.Comprar("342", "123");
		f.fecharCompra("123");
	}
}
