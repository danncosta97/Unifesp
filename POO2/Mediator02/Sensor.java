package Mediator2;

public class Sensor extends Colaborador{
	Float temperature;
	Integer screenSize;
	Pixel[][] camera;
	int sensorId;
		
	public Sensor(int sensorIdentification, Integer screenSize, Float currentTemperature) {
		this.sensorId = sensorIdentification;
		this.screenSize = screenSize;
		this.camera = new Pixel[screenSize][screenSize];
		this.temperature = currentTemperature;
	}
	
	public void setMediator(Mediator m) {
		this.m = m;
	}
	
	public void updateTemperature(Float newTemp) {
		this.temperature = newTemp;
		this.m.send("Temperatura alterada sensor "+this.sensorId, this);
	}
	
	public void updateRGB() {
		for (int i = 0; i<screenSize; i++) {
			for (int j = 0; j<screenSize; j++) {
				//Random r = new Random();
				//camera[i][j].r = (char) r.nextInt();
				//camera[i][j].g = (char) r.nextInt();
				//camera[i][j].b = (char) r.nextInt();
			}
		}
		this.m.send("RBG alterado sensor "+this.sensorId, this);
	}

	@Override
	public void receiveMessage(String s) {
		return;
	}
}

