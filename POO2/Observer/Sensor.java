package Observer;

import java.util.*;

public class Sensor extends Observable{
	Float temperature;
	Integer screenSize;
	Pixel[][] camera;
	
	public Sensor(Long sensorIdentification, Integer screenSize, Float currentTemperature) {
		this.obs_id = sensorIdentification;
		this.screenSize = screenSize;
		this.camera = new Pixel[screenSize][screenSize];
		this.temperature = currentTemperature;
	}
	
	public void updateTemperature(Float newTemp) {
		this.temperature = newTemp;
		this.notificar("'Atualizacao da temperatura !'");
	}
	
	public void updateCamera() {
		
		for (int i = 0; i<screenSize; i++) {
			for (int j = 0; j<screenSize; j++) {
				Random r = new Random();
				camera[i][j].r = (char) r.nextInt();
				camera[i][j].g = (char) r.nextInt();
				camera[i][j].b = (char) r.nextInt();
			}
		}
		
		this.notificar("'Atualizacao da camera !'");
	}
	
	
	
}

