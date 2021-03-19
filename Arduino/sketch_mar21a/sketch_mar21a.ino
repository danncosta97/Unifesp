const int LM35 = 0;
float temperatura = 0;
int ADClido = 0;

const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 11;
const int ledPin4 = 10;
const int Botao1 = 2;
const int Buzzer = 9;
//float Tom = 0; //Variavel para armazenar a nota musical

int pressed=0;
int lastTime=0;
int lock=0;
int debounceDelay=50;
int lastDebounceTime=0;

void setup(){
    pinMode(Buzzer, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(Botao1, INPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);
    Serial.begin(9600);
    analogReference(INTERNAL1V1);
    pinMode(Buzzer, OUTPUT);
}



int buttonState=0;
int lastButtonState=0;
int lastkey=0;
int reading=0;
int key=0;
int m=0;

int debounce(){
    m=millis();
    reading=digitalRead(Botao1);
  
    if (reading != lastButtonState) 
      lastDebounceTime = millis();   
    
    if (m - lastDebounceTime > debounceDelay) {
        if(reading != buttonState) {
            //Serial.print("hola");
            buttonState = reading;
            //Serial.print("hola2");
            if(buttonState==HIGH){
               pressed++;
                return 1;
            }
        }
    }
    lastButtonState = reading;
    return 0;
}

int *bin=(int*)calloc(4,sizeof(int));

void toBin(){
  int aux=0;
  if(pressed==16){
    lock++;
  }
  else{
    aux=pressed;
    for(int i=3;i>=0;i--){
      bin[i]=aux%2;
      aux=aux/2;
    }
  }
}
  
int leds(){
  toBin();
  digitalWrite(ledPin1,bin[0]);
  digitalWrite(ledPin2,bin[1]);
  digitalWrite(ledPin3,bin[2]);
  digitalWrite(ledPin4,bin[3]);
  return 0;
}


int b0=0;
int b1=0;
void ledBlink(){
  b0=millis();
  if(lock==7){
    pressed=0;
    lock=0;
  }
  else if(b0-b1>=500){
    if(lock%2==1){
      digitalWrite(ledPin1,HIGH);
      digitalWrite(ledPin2,HIGH);
      digitalWrite(ledPin3,HIGH);
      digitalWrite(ledPin4,HIGH);
      lock++;
    }
    else{
      digitalWrite(ledPin1,LOW);
      digitalWrite(ledPin2,LOW);
      digitalWrite(ledPin3,LOW);
      digitalWrite(ledPin4,LOW);
      lock++;
    }
    b1=b0;
  }
}


int mi=0;
int mih=0;
void loop(){
    ADClido = analogRead(LM35);
    temperatura = ADClido * 0.1075268817204301;
    mi=millis();
    leds();
    if(lock>0){
      ledBlink();
    }
    else if(debounce()==1){
      Serial.println(temperatura);
    }
    if(temperatura > 25 && mi-mih>=5000){
        digitalWrite(Buzzer, HIGH);
        delayMicroseconds(1000);
        digitalWrite(Buzzer, LOW);
        delayMicroseconds(1000);
        mih=millis();
    }  
}
