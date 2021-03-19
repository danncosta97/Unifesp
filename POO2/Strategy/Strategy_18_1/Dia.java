package Strategy_18_1;

import java.util.Calendar;
import java.util.GregorianCalendar;

public class Dia {
	Strategy day;
	
	GregorianCalendar c = new GregorianCalendar();
	
	public void definirDia() {
		int x = (c.get(Calendar.DAY_OF_WEEK)-1);
		
		switch(x) {
			case 0:
				day = new Domingo();
				break;
			case 1:
				day = new Segunda();
				break;
			case 2:
				day = new Terca();
				break;
			case 3:
				day = new Quarta();
				break;
			case 4:
				day = new Quinta();
				break;
			case 5:
				day = new Sexta();
				break;
			case 6:
				day = new Sabado();
				break;
			default:
				day = null;
		}
		
	}
	
	public void dia() {
		day.printMessage();
	}
}
