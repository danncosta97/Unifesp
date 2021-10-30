// MEGA PORT COM 4 (USB DIR)
#define LDR A0 // A0;
#define START_STATE 0
#define DATA_STATE 1
#define PARITY_STATE 2
#define COMM_STARTED_STATE 3

int state = 0;

int baudDataPosition = 0;

int bitReceived = 0;

int ldrValue = 0;

char charBits = 0;

unsigned long startCycle = 0;
unsigned long clockCycle = 500; // ms
unsigned long initialDelay = 750; // delay para amostrar no tempo central da bit

unsigned long millis_in = 0;
unsigned long millis_out = 0;

unsigned long millis_current = 0;
unsigned long millis_previous = 0;

unsigned long outloop = 0;
unsigned long inloop = 0;
unsigned long betweenloop = 0;

int start=0;

//-----------------------
//Port direct A0 -> PORTF[0]

void setup() {
    Serial.begin(9600);
    // led integrado
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    int state = START_STATE;

    long millis_in = 0;
    long millis_out = 0;

    long millis_current = 0;
    long millis_previous = 0;
}

void loop() {
    millis_previous = millis();
    ldrValue = analogRead(LDR);
    
    /*if(ldrValue < 900 && state == START_STATE) {
        millis_in = millis();
        delay(clockCycle*0.5);
        Serial.print('S');
        delay(clockCycle);
        state = DATA_STATE;
    }

    if(state == DATA_STATE) {
        
        Serial.print(bitReceived);
        charBits = charBits | (bitReceived << baudDataPosition);
        baudDataPosition++;
        if (baudDataPosition > 7){
            baudDataPosition = 0;
            state = START_STATE;
            Serial.print(charBits);
            charBits = 0;
            delay(clockCycle*0.5);
            Serial.print("  ");
            millis_out = millis();
            Serial.println(millis_out - millis_in);
        } else {
            delay(clockCycle);
        }
    }*/

    /*if(ldrValue < 900) {
        millis_in = millis();
        delay(clockCycle*0.5);
        Serial.print('S');
        delay(clockCycle);
        for (int i=0; i<8; i++){
            bitReceived = analogRead(LDR) > 900 ? 1 : 0;
            Serial.print(bitReceived);
            charBits = charBits | (bitReceived << i);
            if(i!=7) delay(clockCycle);
            else delay(clockCycle*0.5);
        }
        Serial.print(charBits);
        charBits = 0;
        Serial.print("  ");
        millis_out = millis();
        Serial.println(millis_out - millis_in);
        //delay(clockCycle*0.5);
    }*/
    /*inloop = millis();
    betweenloop += (inloop - outloop);
    //Serial.println("");
    if(ldrValue < 900) {
        //Serial.println(betweenloop);
        betweenloop=0;
        if(start==0){
           millis_previous = millis();
           start = 1;
        }
        millis_in = millis();
        millis_current = millis();
        if (millis_current - millis_previous >= clockCycle*1.5){
            millis_previous = millis_current;
            Serial.print('S');
            for (int i=0; i<8; i++){
                bitReceived = analogRead(LDR) > 900 ? 1 : 0;
                Serial.print(bitReceived);
                charBits = charBits | (bitReceived << i);
                if(i!=7) {
                    while (millis() - millis_previous < clockCycle){
                        
                    }millis_previous = millis();
                }
                else {
                    while (millis() - millis_previous < clockCycle*0.5){
                        
                    }millis_previous = millis();
                }
            }
            Serial.print(charBits);
            charBits = 0;
            Serial.print("  ");
            millis_out = millis();
            Serial.println(millis_out - millis_in);
            //delay(clockCycle*0.5);
        }
    outloop = millis();
    }*/
    if(ldrValue < 900) {
        while (millis() - millis_previous < clockCycle/2){
            //
        }millis_previous = millis();
        Serial.print('S');
        while (millis() - millis_previous < clockCycle){
            //
        }millis_previous = millis();
        for (int i=0; i<8; i++){
            bitReceived = analogRead(LDR) > 900 ? 1 : 0;
            Serial.print(bitReceived);
            charBits = charBits | (bitReceived << i);
            if(i!=7) {
                while (millis() - millis_previous < clockCycle){
                      //  
                }millis_previous = millis();
            } else { // ultimo bit lido
                while (millis() - millis_previous < 250){
                    //
                }millis_previous = millis();
            }
        }
    }
}
