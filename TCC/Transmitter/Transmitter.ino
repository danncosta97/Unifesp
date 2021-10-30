// NANO PORT COM 5 (USB ESQ)
#define LED_PIN 2
#define BUTTON_PIN A0
#define PERIOD 500

char* string = "This is a test transmission";
int string_length;

long millis_in = 0;
long millis_out = 0;

unsigned long millis_current = 0;
unsigned long millis_previous = 0;

void setup() 
{
    Serial.begin(9600);
    //pinMode(LED_PIN, OUTPUT);
    //pinMode(BUTTON_PIN, INPUT_PULLUP);

    //D7~D2.TX.RX
    DDRD = DDRD | B00000100; // inputs e outputs;
    PORTD = B00000100; // valor alto ou baixo; D2 Alto
    
    string_length = strlen(string);

    long millis_in = 0;
    long millis_out = 0;
}

void loop() 
{
  PORTD = B00000100;
  while (millis() - millis_previous < 5000){
            //
        }
  for(int i = 0; i < string_length; i ++)
  {
    millis_in = millis();
    send_byte(string[i]);
    millis_out = millis();
    Serial.print("  ");
    Serial.println( millis_out - millis_in);
  }
  //delay(1000);
}

void send_byte(char my_byte)
{
    PORTD = B00000000;
    Serial.print('S');
    millis_previous = millis();
    while (millis() - millis_previous < PERIOD){
        //
    }
    for(int i = 0; i < 8; i++)
    {
        if((my_byte&(0x01 << i))!=0){
            PORTD = B00000100;
        } else {
            PORTD = B00000000;
        }
        //digitalWrite(LED_PIN, (my_byte&(0x01 << i))!=0 );
        Serial.print((my_byte&(0x01 << i))!=0);
        millis_previous = millis();
        while (millis() - millis_previous < PERIOD){
            //
        }
    }
}
