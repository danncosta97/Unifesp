package Observer;

public class Main {
	
	public static void main(String[] args) {
		Laboratorio LEF = new Laboratorio("Laboratorio de Experimentos Futuristas");
		Laboratorio LHD = new Laboratorio("Laboratorio dos Hackers da Depressao");
		
		Sensor entrada_ICT = new Sensor((long) 1020231, 1024, 28f);
		Sensor refeitorio_ICT = new Sensor((long) 1420231, 1024, 30f);
		
		entrada_ICT.register(LEF);
		entrada_ICT.register(LHD);
		
		refeitorio_ICT.register(LEF);
		
		entrada_ICT.updateTemperature(29f);
		
		Long current_time = System.currentTimeMillis();
		Long timeToUpdateAgain = System.currentTimeMillis()+2000;
		
		while(current_time < timeToUpdateAgain) {
			current_time = System.currentTimeMillis();
		}
		
		entrada_ICT.updateTemperature(31f);
		refeitorio_ICT.updateTemperature(32f);
		
		
		
	}

}