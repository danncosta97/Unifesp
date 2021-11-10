// MEGA PORT COM 4 (USB DIR)
//--------------------------
// Port direct A0 -> PORTF[0] 0000000$

#include <stdlib.h>

#define LDR A0 // A0

#define TEMT6000 A1 // A1

#define CLK_PERIOD 3

#define IDLE_STATE 0 // Estado de aguardo do proximo Start Bit
#define START_BIT_STATE 1 // Estado de envio do Start Bit
#define DATA_BITS_STATE 2 // Estado de envio dos Bits do char
#define STOP_BIT_STATE 3 // Estado de envio do Stop Bit

#define DEBUG 1 // Habilita e desabilita prints no Serial

/*Prescaler MACROS
//#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) //macro t o
//c l e a r b i t i n s p e c i a l f u n c ti o n r e g i s t e r
//#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit)) //macro t o s e t
b i t i n s p e c i a l f u n c ti o n r e g i s t e r
*/

// Alloca 100 espaços para char (buffer de recebimento) para evitar multiplos Serial.print
// O aumento do buffer deve ocorrer com o detecação de n*100 atingidos
// *Atentar a inserção de '\0' frente a um salvamento em arquivo
char *stringReceivedBuffer = calloc(100, sizeof(char));

// Tempo para printar o buffer
// Após 1s com recebimento de dados HIGH (LED aceso), assume-se fim de string
// já que o sistema permanece 5s ocioso entre envios.
int bufferOutputTimeCounter;
// Bloqueia liberacao do buffer
int bufferOutputLocker;

char charBits; // O char ASCII de fato (8 bits - 1 byte)
int ldrValue;
int bitReceived; // Valor do bit atual
int bitsReceivedAmount; // Quantidade de bits recebido até o momento

int state; // Estado atual do sistema

int baudDataBitIndex; // Indice do bit do char em recepcao

long millisPrevious = 0;

void setup() {
    //Prescale setter (16 bit instead of 128)
    //cbi(ADCSRA,ADPS2) ;
    //sbi(ADCSRA,ADPS1) ;
    //cbi(ADCSRA,ADPS0) ;
    // Habilita o Serial
    Serial.begin(115200);
    // Desliga o LED integrado
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    charBits = 0;
    bitReceived = 0;
    bitsReceivedAmount = 0;

    state = IDLE_STATE;

    baudDataBitIndex = 0;
    
    millisPrevious = 0;

    // Sem saída do buffer inicial vazio
    bufferOutputTimeCounter = 0;
    bufferOutputLocker = 1;
}

void loop() {
    //Serial.println(analogRead(TEMT6000));
    if(state == IDLE_STATE) {
        if (analogRead(TEMT6000) < 500) {
            state = START_BIT_STATE;
            millisPrevious = millis();
        }
        // Momento entre transmissões completas, momento de liberação do buffer
        if (millis() - bufferOutputTimeCounter > 1000 && bufferOutputLocker==0){
            Serial.println(stringReceivedBuffer);
            // Assegura uma única liberação de buffer
            bufferOutputLocker = 1;
        }
    }

    if(state == START_BIT_STATE) {
        //delay para amostragem ótima
        if((millis() - millisPrevious) >= CLK_PERIOD*0.5) {
            //Serial.print("<S");
            state = DATA_BITS_STATE;
            millisPrevious = millis();
        }
    }

    if(state == DATA_BITS_STATE) {
        if((millis() - millisPrevious) >= CLK_PERIOD) {
            bitReceived = analogRead(TEMT6000) > 500 ? 1 : 0;
            //Serial.print(bitReceived);
            charBits = charBits | (bitReceived << baudDataBitIndex);
            baudDataBitIndex++;
            // Caso dos 8 bits do char foram lidos, muda para o estado de STOP BIT
            if(baudDataBitIndex >= 8) {
                baudDataBitIndex = 0;
                state = STOP_BIT_STATE;
            }
            millisPrevious = millis();
        }
    }

    if(state == STOP_BIT_STATE) {
        if((millis() - millisPrevious) >= CLK_PERIOD) {
            //Serial.print("S>");
            //Serial.print(charBits);
            stringReceivedBuffer[bitsReceivedAmount] = charBits;
            bitsReceivedAmount++;

            // temporario para 100 bytes apenas sem '\0'
            if(bitsReceivedAmount>=100){
                bufferOutputTimeCounter = millis();
                bitsReceivedAmount=0;
                bufferOutputLocker = 0;
            }
            
            charBits = 0;
            state = IDLE_STATE;
            millisPrevious = millis();
            //bufferOutputTimeCounter = millis();
        }
    }
}
