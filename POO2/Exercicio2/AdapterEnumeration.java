package AdapterEnumeration;

import java.util.Enumeration;
import java.util.Iterator;

public class AdapterEnumeration implements Iterator<Object> {//adapta enumeration para iterator
	protected Enumeration<?> e;
	
	public AdapterEnumeration (Enumeration<?> x) {
		this.e=x;
	}

	public boolean hasNext() {
		return this.e.hasMoreElements();
	}

	public Object next() {
		return this.e.nextElement();
	}

	public void remove() {
		throw new UnsupportedOperationException();
	}
	
}
