package AdapterEnumeration;

import java.util.*;

public class Main{
	public static void main (String args[]) {
		Vector<String> v = new Vector<String>();
		v.addElement("1");
		v.addElement("2");
		v.addElement("3");
		v.addElement("4");
		v.addElement("5");
		
		Iterator<?> EnumAsIt = new AdapterEnumeration(v.elements());
		
		while (EnumAsIt.hasNext()) {
			System.out.println(EnumAsIt.next());
		}
		
		EnumAsIt.remove();
	}
}
