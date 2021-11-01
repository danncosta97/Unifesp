// MEGA PORT COM 4 (USB DIR)
//--------------------------
// Port direct A0 -> PORTF[0] 0000000$

#define LDR A0 // A0

#define CLK_PERIOD 10

#define IDLE_STATE 0 // Estado de aguardo do proximo Start Bit
#define DELAY_STATE 10 // Estado de delay para amostragem otima
#define START_BIT_STATE 1 // Estado de envio do Start Bit
#define DATA_BITS_STATE 2 // Estado de envio dos Bits do char
#define STOP_BIT_STATE 3 // Estado de envio do Stop Bit

#define DEBUG 1 // Habilita e desabilita prints no Serial

char charBits;
int ldrValue;
int bitReceived;

int state;

int baudDataBitIndex;

long millisPrevious = 0;

void setup() {
    // Habilita o Serial
    Serial.begin(9600);
    // Desliga o LED integrado
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    charBits = 0;
    ldrValue = 0;
    bitReceived = 0;

    state = IDLE_STATE;

    baudDataBitIndex = 0;
    
    millisPrevious = 0;
}

void loop() {

    if(state == IDLE_STATE) {
        if (analogRead(LDR) < 900) {
            state = START_BIT_STATE;

            millisPrevious = millis();
        }
    }

    /*if(state == DELAY_STATE) {
        if((millis() - millisPrevious) >= CLK_PERIOD*0.5) {
            state = START_BIT_STATE;
            millisPrevious = millis();
        }
    }*/

    if(state == START_BIT_STATE) {
        if((millis() - millisPrevious) >= CLK_PERIOD*0.5) {
            Serial.print("<S");
            state = DATA_BITS_STATE;
            millisPrevious = millis();
        }
    }

    if(state == DATA_BITS_STATE) {
        if((millis() - millisPrevious) >= CLK_PERIOD) {
            bitReceived = analogRead(LDR) > 900 ? 1 : 0;
            Serial.print(bitReceived);
            charBits = charBits | (bitReceived << baudDataBitIndex);
            baudDataBitIndex++;
            if(baudDataBitIndex >= 8) {
                baudDataBitIndex = 0;
                state = STOP_BIT_STATE;
            }
            millisPrevious = millis();
        }
    }

    if(state == STOP_BIT_STATE) {
        if((millis() - millisPrevious) >= CLK_PERIOD) {
            Serial.print("S>");
            Serial.println(charBits);
            charBits = 0;
            state = IDLE_STATE;
            millisPrevious = millis();
        }
    }
}
