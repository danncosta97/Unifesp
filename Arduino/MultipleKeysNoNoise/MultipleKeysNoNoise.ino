const int ledPin1 = 13;
const int ledPin2 = 12;
const int ledPin3 = 11;
const int Botao1 = 2;
const int Botao2 = 3;
const int Botao3 = 4;
int EstadoBotao1 = 0;
int EstadoBotao2 = 0;
int EstadoBotao3 = 0;
int pressed=0;
int lock[3]={0};
int buttonState[3]={0};
int lastButtonState[3]={0};
int lastDebounceTime=0;
int debounceDelay=1;
int lastkey=-1;

void setup(){
  pinMode(ledPin1, OUTPUT);
  pinMode(Botao1, INPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(Botao2, INPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(Botao3, INPUT);
    Serial.begin(9600);
}

int* debounce(){
    int reading[3] = {0};
    int key[2]={0};
    key[0]=lastkey;
    key[1]=buttonState[key[0]];
  
    reading[0]=digitalRead(Botao1);
  reading[1]=digitalRead(Botao2);
    reading[2]=digitalRead(Botao3);
    
    //Serial.print(key[0]);
    //Serial.println(key[1]);
  
    //Serial.print(reading[0]);
    //Serial.print(reading[1]);
    //Serial.println(reading[2]);
  
    //Serial.print(lastButtonState[0]);
    //Serial.print(lastButtonState[1]);
    //Serial.println(lastButtonState[2]);
  
    //Serial.print(buttonState[0]);
    //Serial.print(buttonState[1]);
    //Serial.println(buttonState[2]);
  
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
            Serial.print("hola");
          buttonState[key[0]] = reading[key[0]];
            Serial.print("hola");
      if(buttonState[key[0]]==HIGH){
                key[1]=buttonState[key[0]];
            pressed++;
          }
      }
    }
  lastButtonState[0] = reading[0];
  lastButtonState[1] = reading[1];
  lastButtonState[2] = reading[2];
  
  lastkey=key[0];
  
  return key;
}

void loop(){
    int *key;
    key=debounce();
    if (*(key)==0){
      if(*(key+1)==1){
      digitalWrite(ledPin1, HIGH);
    }
    else{
      digitalWrite(ledPin1, LOW);
    }
    }
    if (*(key)==1){
      if(*(key+1)==1){
      digitalWrite(ledPin2, HIGH);
    }
    else{
      digitalWrite(ledPin2, LOW);
    }
    }
    if (*(key)==2){
      if(*(key+1)==1){
      digitalWrite(ledPin2, HIGH);
    }
    else{
      digitalWrite(ledPin2, LOW);
    }
    }
    Serial.print("Pressed: ");
    Serial.println(pressed);
}
