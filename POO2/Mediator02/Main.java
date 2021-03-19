package Mediator2;

public class Main {
	
	public static void main(String[] args) {
		Laboratorio LEF = new Laboratorio("Laboratorio de Experimentos Futuristas");
		Laboratorio LHD = new Laboratorio("Laboratorio dos Hackers da Depressao");
		Laboratorio L01 = new Laboratorio("Laboratorio 01");
		Laboratorio L02 = new Laboratorio("Laboratorio 02");

		
		Sensor entrada_ICT = new Sensor(1020231, 1024, 28f);
		Sensor refeitorio_ICT = new Sensor(1420231, 1024, 30f);
		
		Messenger m = new Messenger();
		
		m.addColaborador(LEF);
		m.addColaborador(LHD);
		m.addColaborador(L01);
		m.addColaborador(L02);
		m.addColaborador(entrada_ICT);
		m.addColaborador(refeitorio_ICT);
		
		refeitorio_ICT.updateRGB();
		refeitorio_ICT.updateTemperature(23f);
	}

}