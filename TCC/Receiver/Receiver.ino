// MEGA PORT COM 4 (USB DIR)
//--------------------------
// Port direct A0 -> PORTF[0] 0000000$
// Port direct D2 -> PORTE[4] 000$0000

#include <stdlib.h>

#define LDR A0 // A0

#define TEMT6000 A1 // A1

#define DIGITAL_TEMT6000 2 // D2

#define CLK_PERIOD 1400 // (em us)
#define CLK_PERIOD_HALF 700 // (em us)

#define IDLE_STATE 0 // Estado de aguardo do proximo Start Bit
#define START_BIT_STATE 1 // Estado de envio do Start Bit
#define DATA_BITS_STATE 2 // Estado de envio dos Bits do char
#define STOP_BIT_STATE 3 // Estado de envio do Stop Bit

#define DEBUG 1 // Habilita e desabilita prints no Serial

// Alloca 100 espaços para char (buffer de recebimento) para evitar multiplos Serial.print
// O aumento do buffer deve ocorrer com o detecação de n*100 atingidos
// *Atentar a inserção de '\0' frente a um salvamento em arquivo
char *stringReceivedBuffer = calloc(101, sizeof(char));

// Tempo para printar o buffer
// Após 1s com recebimento de dados HIGH (LED aceso), assume-se fim de string
// já que o sistema permanece 5s ocioso entre envios.
long bufferOutputTimeCounter;
// Bloqueia liberacao do buffer
int bufferOutputLocker;

char charBits; // O char ASCII de fato (8 bits - 1 byte)
int bitReceived; // Valor do bit atual
int bitsReceivedAmount; // Quantidade de bits recebido até o momento

int state; // Estado atual do sistema

int baudDataBitIndex; // Indice do bit do char em recepcao

long microsPrevious = 0;

void setup() {
    // Habilita o Serial
    Serial.begin(115200);
    // Desliga o LED integrado
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // DIGITAL PIN 7~2.TX.RX
    // E7~E2.TX.RX
    DDRE = DDRE | B00000000; // inputs e outputs; DIGITAL D2 (PORTA E2) input

    charBits = 0;
    bitReceived = 0;
    bitsReceivedAmount = 0;

    state = IDLE_STATE;

    baudDataBitIndex = 0;
    
    microsPrevious = 0;

    // Sem saída do buffer inicial vazio
    bufferOutputTimeCounter = 0;
    bufferOutputLocker = 1;
}

void loop() {
    //Serial.println(analogRead(TEMT6000));
    //Serial.println(digitalRead(DIGITAL_TEMT6000));
    //Serial.print(PINE>>4 & B1);
    //delay(1000);
    if(state == IDLE_STATE) {
        if (!(PINE>>4 & B1)) {
            state = START_BIT_STATE;
            microsPrevious = micros();
        }
        // Momento entre transmissões completas, momento de liberação do buffer
        if ( ((micros() - bufferOutputTimeCounter) > 2000000) && bufferOutputLocker==0){
            Serial.println(stringReceivedBuffer);
            // Assegura uma única liberação de buffer
            bufferOutputLocker = 1;
        }
    }

    if(state == START_BIT_STATE) {
        //delay para amostragem ótima
        if((micros() - microsPrevious) >= CLK_PERIOD_HALF) {
            //Serial.print("<S");
            state = DATA_BITS_STATE;
            microsPrevious = micros();
        }
    }

    if(state == DATA_BITS_STATE) {
        if((micros() - microsPrevious) >= CLK_PERIOD) {
            bitReceived = PINE>>4 & B1;
            //Serial.print(bitReceived);
            charBits = charBits | (bitReceived << baudDataBitIndex);
            baudDataBitIndex++;
            // Caso dos 8 bits do char foram lidos, muda para o estado de STOP BIT
            if(baudDataBitIndex >= 8) {
                baudDataBitIndex = 0;
                state = STOP_BIT_STATE;
            }
            microsPrevious = micros();
        }
    }

    if(state == STOP_BIT_STATE) {
        if((micros() - microsPrevious) >= CLK_PERIOD) {
            //Serial.print("S>");
            //Serial.print(charBits);
            stringReceivedBuffer[bitsReceivedAmount] = charBits;
            bitsReceivedAmount++;

            // temporario para 100 bytes apenas sem contar '\0'
            if(bitsReceivedAmount>=100){
                stringReceivedBuffer[100] = '\0';
                bufferOutputTimeCounter = micros();
                bitsReceivedAmount=0;
                bufferOutputLocker = 0;
            }
            
            charBits = 0;
            state = IDLE_STATE;
            microsPrevious = micros();
        }
    }
}
