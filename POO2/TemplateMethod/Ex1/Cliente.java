package Ex1;

import java.util.Arrays;

public class Cliente {

	public static void main(String args[]) {
		String textos[] = new String[5];
		textos[0] = "Inglaterra";
		textos[1] = "Japao";
		textos[2] = "Alemanha";
		textos[3] = "Brasil";
		textos[4] = "Italia";
		
		Arrays.sort(textos, new OrganizaLetra());
		
		for(int cont=0;cont<5;cont++) {
			System.out.println(textos[cont]);
		}
	}
}
