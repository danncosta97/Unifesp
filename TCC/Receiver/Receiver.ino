// MEGA PORT COM 5
#define LDR A0 // A0;
#define START_STATE 0
#define DATA_STATE 1
#define PARITY_STATE 2
#define COMM_STARTED_STATE 3

//const char frase = "D";
const int startAndParitySize = 2;
int fraseSize = 0;
int parityBit = 0;
int frasePosition = 0;

int state = 0; //1 dados, 2 paridade, 3 finalizado

unsigned long startCycle = 0;
unsigned long clockCycle = 50; // ms
unsigned long intialDelay = clockCycle + (clockCycle/2); // delay para amostrar no tempo central da bit


int baudBitPosition; // excluindo startBit

char charBits = 0;

int delChar = 0; // transmissor provavelmente reiniciando (@see)

int commStarted = 0; // para inserção do delay incial 

int receivedBit = 0;

long temp1 = 0;
long temp2 = 0;


void setup() {
    Serial.begin(9600);
    
    // led integrado
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    //fraseSize = strlen(frase);
    baudBitPosition = 0;
    startCycle = millis();

}

void loop() {
    int ldrValue = analogRead(A0);
    
    if (state == START_STATE && ldrValue < 900) { // bit de início detectado
        state = DATA_STATE;  // vai para leitura dos dados efetivos (caracter)
        temp1 = millis();
        delay(intialDelay);
    }// "baudBitPosition -1" de startBit

    if (state == COMM_STARTED_STATE) {
        delay(clockCycle);
        if (analogRead(A0) < 900) { // temos mais um startbit de baud
            delay(clockCycle);
            state = DATA_STATE;
        } else {
            state = START_STATE;
        }
    }

    if (state == DATA_STATE && baudBitPosition < 8) { // leitura dos 8 bits do caracter
       
        receivedBit = (analogRead(A0) > 900) ? 1 : 0;
        // bitwise
        charBits = charBits | (receivedBit << baudBitPosition);
        if(receivedBit == 1) {
            parityBit = (1 + parityBit)%2;
            //delChar++;
        }
        
        baudBitPosition++;
        if (baudBitPosition >= 8) { // 8 bits de dados lidos (caracter). Vai para paridade
            state = PARITY_STATE;
        }
        Serial.print(receivedBit);
        
        delay(clockCycle);
    }

    if (state == PARITY_STATE) { // verifica a paridade

        receivedBit = (analogRead(A0) > 900) ? 1 : 0;
             
        if (parityBit != receivedBit) {
            Serial.print("[*ERROR*]");
        } else {
            Serial.println(charBits);
        }
        //delay(250);
        charBits = 0;
        baudBitPosition = 0; 
        state = COMM_STARTED_STATE;
    }
}
