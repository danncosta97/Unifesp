package Ex1;

import java.util.Comparator;

public class OrganizaLetra implements Comparator {

	public OrganizaLetra() {
		
	}
	public int compare(Object texto1, Object texto2) {
		
		String t1 = (String) texto1;
		String t2 = (String) texto2;
		int f1 = t1.length() - 1;
		int f2 = t2.length() - 1;
		
		if(t1.charAt(0)>t1.charAt(0)) return 1;
		if(t1.charAt(0)<t1.charAt(0)) return -1;
		if(t1.charAt(0)==t1.charAt(0)) return 0;
		
		return 0;
	}
	
}
