const int pButton=8;
const int pTr=13;
const int pTy=12;
const int pTg=11;
const int pWr=10;
const int pWg=9;

int tracker=0;
int lastt=0;
int bPressed=0;
unsigned long lastTime;

int buttonState=LOW;
int lastButtonState = LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int block=0;

void setup(){
  pinMode(pButton, OUTPUT);
  pinMode(pTr, OUTPUT);
  pinMode(pTy, OUTPUT);
  pinMode(pTg, OUTPUT);
  pinMode(pWr, OUTPUT);
  pinMode(pWg, INPUT);
  digitalWrite(pTr,HIGH);
  digitalWrite(pTy,LOW);
  digitalWrite(pTg,LOW);
  digitalWrite(pWr,LOW);
  digitalWrite(pWg,HIGH);
  Serial.begin(9600);
}

int timePassed(){
  int lt=lastTime;
  int mil=millis();
  Serial.print("\n");
  //Serial.print(lastTime);Serial.print("\n");
  //Serial.print(mil-lt);Serial.print("\n");
  if(tracker==0 && mil-lt>=5000){
    tracker=1;
    lastTime=millis();
  }
  else if(tracker==1 && mil-lt>=12500){
    tracker=2;
    lastTime=millis();
  }
  else if(tracker==2 && mil-lt>=2500){
    tracker=0;
    lastTime=millis();
  }
  return tracker;
}

void debounce(){
  int mil=millis();
  int reading = digitalRead(pButton);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if(buttonState==HIGH){
        bPressed++;
        if (tracker==0 && block==0) {
        lastTime+=1000;
        block=1;
        }
      else if(tracker==1 && block==0){
          lastTime-=(millis()-lastTime/2);
          block=1;
        }
      }
    }
  }
  lastButtonState = reading;
}

void loop(){
  int t=timePassed();
  debounce();
  String st="pressed";
  st=st+bPressed;
  Serial.println(st);
  if(t==0){
    digitalWrite(pTr,HIGH);
    digitalWrite(pTy,LOW);
    digitalWrite(pTg,LOW);
    digitalWrite(pWr,LOW);
    digitalWrite(pWg,HIGH);
  }
  else if(t==2){
    digitalWrite(pTr,LOW);
    digitalWrite(pTy,HIGH);
    digitalWrite(pTg,LOW);
    digitalWrite(pWr,HIGH);
    digitalWrite(pWg,LOW);
  }
  else if(t==1){
    digitalWrite(pTr,LOW);
    digitalWrite(pTy,LOW);
    digitalWrite(pTg,HIGH);
    digitalWrite(pWr,HIGH);
    digitalWrite(pWg,LOW);
  }
  if(t!=lastt){
    block=0;
  }
  lastt=t;
}
