const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 11;
const int Botao1 = 2;
const int Botao2 = 3;
const int Botao3 = 4;
const int Buzzer = 10; //O buzzer está colocado no pino 10
int EstadoBotao1 = 0;
int EstadoBotao2 = 0;
int EstadoBotao3 = 0;
float Tom = 0; //Variavel para armazenar a nota musical

int pressed=0;
int lastTime=0;
int lock=0;
int debounceDelay=50;
int lastDebounceTime=0;
int checker=0;
int lastp=-1;

int *buttonState=(int*)calloc(3,sizeof(int));
int *lastButtonState=(int*)calloc(3,sizeof(int));
int *lastkey=(int*)calloc(2,sizeof(int));
int *reading=(int*)calloc(3,sizeof(int));
int *key=(int*)calloc(2,sizeof(int));


void setup() {
    pinMode(Buzzer, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(Botao1, INPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(Botao2, INPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(Botao3, INPUT);
    Serial.begin(9600);
}

int* debounce(){
    key[0]=lastkey[0]; //button pressed, from 0 to 2
    key[1]=lastkey[1]; //able to check next button on pw
  
    reading[0]=digitalRead(Botao1);
    reading[1]=digitalRead(Botao2);
    reading[2]=digitalRead(Botao3);
  
    if (reading[0] != lastButtonState[0]) {
      lastDebounceTime = millis();
        key[0]=0;   
    }
    else if (reading[1] != lastButtonState[1]) {
    lastDebounceTime = millis();
        key[0]=1;
    }
    else if (reading[2] != lastButtonState[2]) {
        lastDebounceTime = millis();
        key[0]=2;
    }
    if ((millis() - lastDebounceTime) > debounceDelay && key[0]>=0) {
      if (reading[key[0]] != buttonState[key[0]]) {
            //Serial.print("hola");
            buttonState[key[0]] = reading[key[0]];
            //Serial.print("hola2");
            if(buttonState[key[0]]==HIGH){
              pressed++;
              key[1]=1;
            }
        }
    }
  lastButtonState[0] = reading[0];
  lastButtonState[1] = reading[1];
  lastButtonState[2] = reading[2];
  
  lastkey[0]=key[0];
  lastkey[1]=key[1];
  return key;
}

int password(int value){ //botoes sequencia (1,3,2,2,1)
    
    if(pressed==1 && value==0){
      checker++;
    }
    else if(pressed==2 && value==2){
      checker++;
    }
    else if(pressed==3 && value==1){
      checker++;
    }
    else if(pressed==4 && value==1){
      checker++;
    }
    else if(pressed==5 && value==0){
      checker++;
    }
  Serial.print("checker: ");
  Serial.println(checker);
    
  
    if(pressed==5 && checker!=5){
        checker=0;
        pressed=0;
      return 0;
    }
    if(pressed==5 && checker==5){
        checker=0;
        pressed=0;
      return 1;
    }
    else return -1;
}

void loop(){
    int *k=debounce();
    int p=lastp;  
  
    if(k[1]==1 && Tom==0 && lock==0){
      Serial.println(k[0]);
      p=password(k[0]);
      Serial.println(p);
      lastkey[1]=0;
    }
  
    if (p==1){ //pass correto
        
      
        if(lock==6){
          lastTime=millis();
          lock=0;
          Tom=0;
          p=-1;
        }
        if(lock%2==1 && millis()-lastTime<50){
          digitalWrite(Buzzer, HIGH); // Liga buzzer
            delayMicroseconds(Tom); // Espera o tempo proporcional ao
          digitalWrite(Buzzer, LOW); // Desliga buzzer
            delayMicroseconds(Tom); // Espera o tempo proporcional ao
            //comprimento de onda da nota musical em milisegundos 
        }
        else if(lock%2==0 && millis()-lastTime>=100) { //enquanto Tom for maior que zero faça o que esta
        //descrit o baixo:
            Tom+=100;
            lock++;
            lastTime=millis();
            digitalWrite(ledPin1, HIGH);
          digitalWrite(ledPin2, HIGH);
          digitalWrite(ledPin3, HIGH);
        }
        else if(lock%2==1 && millis()-lastTime>=50){
            lock++;
            lastTime=millis();
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, LOW);
        }
    }
    
    else if (p==0){//pass errado
        if(lock%2==0 && millis()-lastTime>100){
          lastTime=millis();
          lock++;
          digitalWrite(ledPin1,HIGH);
        }
        else if(lock%2==1 && millis()-lastTime>300){
          lastTime=millis();
          digitalWrite(ledPin1,LOW);
          lock++;
        }
        if(lock==4){
          lock=0;
          p=-1;
        }
    }
    lastp=p;
}
