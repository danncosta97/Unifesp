// NANO PORT COM 5 (USB ESQ)
//--------------------------
// Port direct D2 -> PORTD[2] 00000$00

#define CLK_PERIOD 10 // Precisa ser igual ao do receptor

#define START_STATE 0 // Estado de inicializacao, tempo para iniciar o receptor
#define START_BIT_STATE 1 // Estado de envio do Start Bit
#define DATA_BITS_STATE 2 // Estado de envio dos Bits do char
#define STOP_BIT_STATE 3 // Estado de envio do Stop Bit

#define DEBUG 1 // Habilita e desabilita prints no Serial

char* string = "This is a test transmission";
int stringLength;
int stringLengthSent;

int state;

int baudDataBitIndex;

unsigned long millisPrevious;

void setup() {
    // Habilita o Serial
    Serial.begin(9600);
    // Desliga o LED integrado
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // D7~D2.TX.RX
    DDRD = DDRD | B00000100; // inputs e outputs; D2 Output
    PORTD = B00000100; // valor alto ou baixo; D2 Alto

    stringLength = 0;
    stringLength = strlen(string);
    stringLengthSent = 0;

    state = START_STATE;
    baudDataBitIndex = 0;

    millisPrevious = 0;
    millisPrevious = millis();
}

void loop() {
    //PORTD = B00000100;

    // Matém o LED aceso por 5s.
    if(state == START_STATE) {
        if((millis() - millisPrevious) >= 5000) {
            state = START_BIT_STATE;
            
            millisPrevious = millis();
        }
    }

    // Faz o envio do Start Bit (nível baixo).
    if(state == START_BIT_STATE) {
        if((millis() - millisPrevious) >= CLK_PERIOD) {
            PORTD = B00000000;
            state = DATA_BITS_STATE;
            
            if(DEBUG) Serial.print("<S");
            
            millisPrevious = millis();
        }
    }

    // Faz o envio dos Bits do Char;
    // Ao enviar 8 bits (baudDataBitIndex==8), vai para o Stop Bit
    // e incrementa para o próximo caracter da string (stringLengthSent++).
    if(state == DATA_BITS_STATE) {
        if((millis() - millisPrevious) >= CLK_PERIOD) {
            // Bits de dados (LSB para MSB)
            if((string[stringLengthSent] & (0x01 << baudDataBitIndex)) != 0) {
                PORTD = B00000100;
            } else {
                PORTD = B00000000;
            }
            
            if(DEBUG) Serial.print((string[stringLengthSent] & (0x01 << baudDataBitIndex)) != 0);
            
            baudDataBitIndex++;
            
            if(baudDataBitIndex >= 8) {
                state = STOP_BIT_STATE;
                baudDataBitIndex = 0;
                stringLengthSent++;
            }
            
            millisPrevious = millis();
        }
    }

    // Faz o envio do Stop Bit (nível alto) e volt para o Start Bit;
    // Se a qtd de char enviados for maior ou igual ao tamanho da frase
    // Volta para estado de inicialização do sistema.
    if(state == STOP_BIT_STATE) {
        if((millis() - millisPrevious) >= CLK_PERIOD) {
            PORTD = B00000100;
            state = START_BIT_STATE;
            
            if(DEBUG) Serial.println("S>");
            
            if(stringLengthSent >= stringLength){
                    stringLengthSent = 0;
                    state = START_STATE;
            }
            
            millisPrevious = millis();
        }
    }
}
