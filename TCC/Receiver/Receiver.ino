// MEGA PORT COM 4 (USB DIR)
//--------------------------
// Port direct A0 -> PORTF[0] 0000000$
#define LDR A0 // A0
#define CLK_PERIOD 500

int baudDataBitIndex = 0;
char charBits;

long millis_current = 0;
long millis_previous = 0;

int ldrValue;
int bitReceived;

void setup() {
    Serial.begin(9600);
    // LED integrado
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    charBits = 0;
    ldrValue = 0;
    bitReceived = 0;
    
    millis_current = 0;
    millis_previous = 0;
}

void loop() {
    millis_previous = millis();
    ldrValue = analogRead(LDR);
    if(ldrValue < 900) {
        // Amostragem ótima - centro do bit
        while (millis() - millis_previous < CLK_PERIOD*0.5){
            //
        }millis_previous = millis();
        Serial.print("<S");
        while (millis() - millis_previous < CLK_PERIOD) {
            //
        }millis_previous = millis();
        
        // Bits de dados (LSB para MSB)
        for (baudDataBitIndex=0; baudDataBitIndex<8; baudDataBitIndex++){
            bitReceived = analogRead(LDR) > 900 ? 1 : 0;
            Serial.print(bitReceived);
            charBits = charBits | (bitReceived << baudDataBitIndex);
            while (millis() - millis_previous < CLK_PERIOD){
                //
            }millis_previous = millis();
        }
        Serial.print("S>");
        Serial.println(charBits);
        charBits = 0;
    }
}
