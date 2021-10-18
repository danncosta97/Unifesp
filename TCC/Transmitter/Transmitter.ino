#include <stdio.h>
#include <string.h>
#define LED 2 // D2;

const char* frase = "Frase Teste De Novo";
const int startAndParitySize = 2;
int fraseSize = 0;
int parityBit = 0; // single
int frasePosition = 0;


unsigned long startCycle = 0;
unsigned long clockCycle = 500; // ms

int baudBitPosition; // posicao bit no baud

int readyToStart = 0;

long temp1 = 0;
long temp2 = 0;

void setup() {
    Serial.begin(9600);
    
    // led integrado
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // led emissor
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);

    fraseSize = strlen(frase);
    baudBitPosition = 0;
    startCycle = millis();
}

void loop() {

    // tempo para resetar o receptor
    // evitar captacao de dados na inicializacao
    if(readyToStart == 0){
        delay (5000); readyToStart=1;
        startCycle = millis();
    }
    
    if (millis() - startCycle >= clockCycle && frasePosition < fraseSize){
    
        startCycle = millis();
    
        if (baudBitPosition==0) { //start bit 0
            temp1 = millis();
            digitalWrite(LED, 0);
            Serial.print(0);
            baudBitPosition++;
            delay(clockCycle);
        } else if (baudBitPosition<9) {
            int charBit = ((frase[frasePosition] >> (baudBitPosition-1)) & 1);
            digitalWrite(LED, charBit);
            if ((frase[frasePosition] >> (baudBitPosition-1)) & 1) {
                parityBit = (1 + parityBit)%2;
            }
            Serial.print(charBit);
            baudBitPosition++;
            delay(clockCycle);
        } else { // single parityBit
            digitalWrite(LED, parityBit);
            baudBitPosition=0;
            frasePosition++;
            Serial.print(parityBit);
            Serial.print("\n");
            delay(clockCycle);
            temp2 = millis();
            Serial.print(temp2 - temp1);
            
        }
 
    }

    if (frasePosition >= fraseSize) {
        digitalWrite(LED, 1);
        Serial.print("STRING FINISHED");
        //delay(100);
        exit(0);
    }
    
}
