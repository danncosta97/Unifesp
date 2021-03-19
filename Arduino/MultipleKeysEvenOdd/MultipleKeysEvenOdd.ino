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
int lastTime=0;
int lock=0;
int debounceDelay=50;
int lastDebounceTime=0;

int *buttonState=(int*)calloc(3,sizeof(int));
int *lastButtonState=(int*)calloc(3,sizeof(int));
int *lastkey=(int*)calloc(2,sizeof(int));
int *reading=(int*)calloc(3,sizeof(int));
int *key=(int*)calloc(2,sizeof(int));

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
    key[0]=lastkey[0]; //key
    key[1]=lastkey[1]; //make blink or not
  
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
              if(key[0]==0||key[0]==1){
              pressed++;
                }
                else if(key[0]==2){
                  key[1]=1;
                }
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

void loop(){
    
    //Serial.println("hola8");
    int *key;
    key=debounce();
    //Serial.println(lock);
    //Serial.println(key[0]);
    //Serial.println(key[1]);
    
    if (key[1]==0){
        //Serial.println("hola3");
        if(pressed%2==0){
          digitalWrite(ledPin3, HIGH);
            digitalWrite(ledPin2, LOW);
        }
      else{
          digitalWrite(ledPin2, HIGH);
            digitalWrite(ledPin3, LOW);
        }
    }
  
    else{
        int mil=millis();
        if(lock==0){
            //Serial.println(lock);
            //Serial.println("hola4");
            digitalWrite(ledPin1, HIGH);
          lastTime=mil;
            lock++;
            //delay(5000);
        }
      
        else if(lock%2==1 && mil-lastTime>500){
            //Serial.println(lock);
            //Serial.println("###########hola5");
          lock++;
          digitalWrite(ledPin1, LOW);
            lastTime=mil;
            //delay(5000);
        }
      
        else if(lock%2==0 && mil-lastTime>200){
            //Serial.println(lock);
            //Serial.println(key[0]);
            //Serial.println(key[1]);
            //Serial.println("%%%%%%%%%%hola6");
          //delay(5000);
            lastTime=mil;
          if(lock==4){
              //Serial.println(lock);
              //Serial.println(">>>>>>>>>>>>>>hola7");
              //delay(5000);
                pressed=0;
              lock=0;
                key[0]=0;
                key[1]=0;
                lastkey[0]=0;
                lastkey[1]=0;
            }
            else{
              lock++;
              digitalWrite(ledPin1, HIGH);
            }
        }   
    }
    Serial.print("Pressed: ");
    Serial.println(pressed);
}
