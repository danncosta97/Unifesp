// NANO PORT COM 5 (USB ESQ)
//--------------------------
// Port direct D2 -> PORTD[2] 00000$00
#define CLK_PERIOD 500

char* string = "This is a test transmission";
int stringLength = 0;
int baudDataBitIndex = 0;

unsigned long millis_current = 0;
unsigned long millis_previous = 0;

void setup() {
    Serial.begin(9600);
    // LED integrado
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // D7~D2.TX.RX
    DDRD = DDRD | B00000100; // inputs e outputs;
    PORTD = B00000100; // valor alto ou baixo; D2 Alto
    
    stringLength = strlen(string);

    long millis_in = 0;
    long millis_out = 0;
}

void loop() {
    PORTD = B00000100;
  
    //Start System
    while (millis() - millis_previous < 5000) {
    
    }millis_previous = millis();
      
    for(int i = 0; i < stringLength; i ++) {
        startBit();
        
        dataBits(string[i]);
        
        stopBit();
    }
  
}

void startBit() {
    PORTD = B00000000;
    Serial.print("<S");
    while (millis() - millis_previous < CLK_PERIOD) {
        //
    }millis_previous = millis();
}

void dataBits(char dataByte){
    for(baudDataBitIndex=0; baudDataBitIndex<8; baudDataBitIndex++) {
        // Envio do LSB para o MSB
        if((dataByte & (0x01 << baudDataBitIndex)) != 0) {
            PORTD = B00000100;
        } else {
            PORTD = B00000000;
        }
        Serial.print((dataByte & (0x01 << baudDataBitIndex)) != 0);
        while (millis() - millis_previous < CLK_PERIOD) {
            //
        }millis_previous = millis();
    }
}

void stopBit() {
    PORTD = B00000100;
    Serial.println("S>");
    while (millis() - millis_previous < CLK_PERIOD) {
        //
    }millis_previous = millis();
}
