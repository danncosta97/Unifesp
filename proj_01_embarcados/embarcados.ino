#include <Wire.h>
#include <SPI.h>
//#include <MFRC522.h>
#include <LiquidCrystal.h>
//#include <Stepper.h>
#include <stdlib.h>
//#include "RTClib.h"
//#include <SoftwareSerial.h>
//SoftwareSerial bluetooth(2,3); //TX, RX (Bluetooth)

/*               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15*/

//rtc
char diaSemana[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};

const int stepsPerRevolution = 32;  // change this to fit the number of steps per revolution
// for your motor
float motorSpeed=50000;

//PINS################################################################
//#define SS_PIN 53
//#define RST_PIN 5
//MFRC522 mfrc522(SS_PIN, RST_PIN);
//RTC_DS3231 rtc;

LiquidCrystal lcd(29,28,27,26,25,24);

// motor
int motorPin4=42;
int motorPin3=43;
int motorPin2=44;
int motorPin1=45;

//ultrassom
int trigPin = 40;    // Trigger
int echoPin = 41;    // Echo

//buzzer
int buzzer = 4 ;

//PIR
int pir=30;
int lamp=31;

//VARIAVEIS#########################################################
int k=0;

//ultrassom
float cm=0;
long time_us_d=0;
int timetraveled=0;
long stopb=0;
int stopbuzzer=0;
float lastd=0;
int lockerbuzzer=0;

//motor
long tmotor=millis();
int error=0;

//lcd
int buttonlcd=34;
int bdisplay=1;
int lastButtonState=0;
unsigned long lastDebounceTime=0;
unsigned int debounceDelay=150;
int buttonState=0;

//SETUP
void setup() {
  Serial.begin(9600);   // Inicia a serial
  Serial3.begin(9600);
  //bluetooth.begin(9600);
  //rtc
  //rtc.begin();
  
  //rfid
  //SPI.begin();      // Inicia  SPI bus
  //mfrc522.PCD_Init();   // Inicia MFRC522  
  
  //ultrassom/buzzer
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  
  //PIR
  pinMode(lamp, OUTPUT);
  pinMode(pir, INPUT);

  //lcd
  lcd.begin(16, 2); // Define o número de colunas e linhas do display LCD usado.*/
}

//botao display LCD
void debounce() {
  //Serial.println(bdisplay);
  int reading = digitalRead(buttonlcd);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
          bdisplay++;
        if(bdisplay==3){
          bdisplay=0;
        }
      }
    }
  }
  lastButtonState = reading;
}

//botao abertura do portao
int por=10;
int lastButtonStatet=0;
unsigned long lastDebounceTimet=0;
unsigned int debounceDelayt=150;
int buttonStatet=0;
void debouncet() {
  int readingt = digitalRead(por);
  if (readingt != lastButtonStatet) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTimet) > debounceDelayt) {
    if (readingt != buttonState) {
      buttonStatet = readingt;
      if (buttonStatet == LOW && k==0) {
          k=1;
          tmotor=millis();
      }
    }
  }
  lastButtonStatet = readingt;
}

/*byte readCard[4];
int getID() {
  // Getting ready for Reading PICCs
  mfrc522.PICC_ReadCardSerial();
  mfrc522.PICC_IsNewCardPresent();
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    Serial.println("asdsaf");
    return 0;
  }
  //if(! mfrc522.PICC_IsNewCardPresent()){
    //Serial.println("k");
    //return 0;
  //}
  // There are Mifare PICCs which have 4 byte or 7 byte UID care if you use 7 byte PICC
  // I think we should assume every PICC as they have 4 byte UID
  // Until we support 7 byte PICCs
  Serial.println("Scanned PICC's UID:");
  //mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}*/

//int aux=0;
//String id="";
long lcdtime=0; //update lcd each 1 seacond
long m=0; //millis
byte i=0; //bluetooth byte
//long rfid=0;
long serial=0; //serial update each 1 second
//LOOP
int incomingByte;

void loop() {
  m=millis();
  debounce();
  
  debouncet();
  //look for some command from smartphone bluetooth
  if (Serial3.available() > 0) {
          incomingByte = Serial3.read();
       //open the gate
      if (incomingByte == 'o') {
          k=1; //value for opening gate
          Serial3.println("Comando de abertura");
          tmotor=millis();
      }
      //print house status on smartphone
      else if (incomingByte == 'k') {
          if(cm>15 || cm==0){
            Serial3.println("Garagem Vazia");
          }else{
            Serial3.println("Garagem Com carro");
          }
          if(digitalRead(pir)==1){
            Serial3.println("Ha' gente no porao");
          }else{
            Serial3.println("Ninguem no porao");
          }
          if(k==0){
            Serial3.println("Portao Fechado");
          }
          if(k==1){
            Serial3.println("Portao Abrindo");
          }
          if(k==2){
            Serial3.println("Portao Fechando");
          }
          if(k==3){
            Serial3.println("Portao Aberto");
          }
      }
  }

  if(k==1){
     digitalWrite(motorPin1, HIGH); //1
     digitalWrite(motorPin2, LOW);
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin4, LOW);
     delayMicroseconds(motorSpeed);
     // 2
     digitalWrite(motorPin1, HIGH);
     digitalWrite(motorPin2, HIGH);
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin4, LOW);
     delayMicroseconds (motorSpeed);
     // 3
     digitalWrite(motorPin1, LOW);
     digitalWrite(motorPin2, HIGH);
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin4, LOW);
     delayMicroseconds(motorSpeed);
     // 4
     digitalWrite(motorPin1, LOW);
     digitalWrite(motorPin2, HIGH);
     digitalWrite(motorPin3, HIGH);
     digitalWrite(motorPin4, LOW);
     delayMicroseconds(motorSpeed);
     // 5
     digitalWrite(motorPin1, LOW);
     digitalWrite(motorPin2, LOW);
     digitalWrite(motorPin3, HIGH);
     digitalWrite(motorPin4, LOW);
     delayMicroseconds(motorSpeed);
     // 6
     digitalWrite(motorPin1, LOW);
     digitalWrite(motorPin2, LOW);
     digitalWrite(motorPin3, HIGH);
     digitalWrite(motorPin4, HIGH);
     delayMicroseconds (motorSpeed);
     // 7
     digitalWrite(motorPin1, LOW);
     digitalWrite(motorPin2, LOW);
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin4, HIGH);
     delayMicroseconds(motorSpeed);
     // 8
     digitalWrite(motorPin1, HIGH);
     digitalWrite(motorPin2, LOW);
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin4, HIGH);
     delayMicroseconds(motorSpeed);
  }
  
  else if(k==2){
     digitalWrite(motorPin4, HIGH);//1
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin2, LOW);
     digitalWrite(motorPin1, LOW);
     delayMicroseconds(motorSpeed);
     // 2
     digitalWrite(motorPin4, HIGH);
     digitalWrite(motorPin3, HIGH);
     digitalWrite(motorPin2, LOW);
     digitalWrite(motorPin1, LOW);
     delayMicroseconds (motorSpeed);
     // 3
     digitalWrite(motorPin4, LOW);
     digitalWrite(motorPin3, HIGH);
     digitalWrite(motorPin2, LOW);
     digitalWrite(motorPin1, LOW);
     delayMicroseconds(motorSpeed);
     // 4
     digitalWrite(motorPin4, LOW);
     digitalWrite(motorPin3, HIGH);
     digitalWrite(motorPin2, HIGH);
     digitalWrite(motorPin1, LOW);
     delayMicroseconds(motorSpeed);
     // 5
     digitalWrite(motorPin4, LOW);
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin2, HIGH);
     digitalWrite(motorPin1, LOW);
     delayMicroseconds(motorSpeed);
     // 6
     digitalWrite(motorPin4, LOW);
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin2, HIGH);
     digitalWrite(motorPin1, HIGH);
     delayMicroseconds (motorSpeed);
     // 7
     digitalWrite(motorPin4, LOW);
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin2, LOW);
     digitalWrite(motorPin1, HIGH);
     delayMicroseconds(motorSpeed);
     // 8
     digitalWrite(motorPin4, HIGH);
     digitalWrite(motorPin3, LOW);
     digitalWrite(motorPin2, LOW);
     digitalWrite(motorPin1, HIGH);
     delayMicroseconds(motorSpeed);
  }
  
  if(k==1 && m-tmotor>10000){
    k=3;
  }
  else if(k==3 && m-tmotor>15000 && m-tmotor<25010){
    k=2;
  }
  else if(k==2 && m-tmotor>25000 && m-tmotor<35010){
    k=0;
  }
  
  /*if(k==5 && tmotor%1001==1000 && error<=4){
    aux=!aux;
    digitalWrite(lamp, aux);
    error++;
  }
  if(error==4){
    error=0;
    k=0;
  }*/
  
  //pir
  if(digitalRead(pir)==1){
    //Serial.println("SIMONE IS HERE");
    digitalWrite(lamp, HIGH);
  }
  else{
    digitalWrite(lamp, LOW);
  }
  
  
   //ultrassom/buzzer
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  timetraveled = pulseIn(echoPin, HIGH, 20000);
  cm = (timetraveled/2)*0.0343;
  
  if(stopbuzzer==0){
    if(cm<6 && cm>5 && m-time_us_d>500){
        time_us_d=m;
        digitalWrite (buzzer, HIGH) ;
        delayMicroseconds(200) ;
        digitalWrite (buzzer, LOW) ;
        delayMicroseconds(200) ;
     }
    else if(cm<5 && cm>4 && m-time_us_d>250){
        time_us_d=m;
        digitalWrite (buzzer, HIGH) ;
        delayMicroseconds(200) ;
        digitalWrite (buzzer, LOW) ;
        delayMicroseconds(200) ;
     }
    else if(cm<4 && cm>3 && m-time_us_d>100){
        time_us_d=m;
        digitalWrite (buzzer, HIGH) ;
        delayMicroseconds(200) ;
        digitalWrite (buzzer, LOW) ;
        delayMicroseconds(200) ;
     }
    if(cm<3 && cm>1){
        digitalWrite (buzzer, HIGH) ;
        delayMicroseconds(200) ;
        digitalWrite (buzzer, LOW) ;
        delayMicroseconds(200) ;
     }
     
  }
  if(m-stopb>1000){
    stopb=m;
    lastd=cm;
    lockerbuzzer++;
  }
  if(cm<lastd+0.4 && cm>lastd-0.4 && lockerbuzzer>=4){
    stopbuzzer=1;
    lockerbuzzer=0;
  }
  if(cm<lastd-0.4){
    stopbuzzer=0;
  }
  

  //lcd
  if(m-lcdtime>1000){
     lcdtime=m;
     lcd.clear();
     if(bdisplay==0){
        lcd.setCursor(0,0);
        lcd.print("Garagem");
        lcd.setCursor(0,1);
        if(cm>15 || cm==0){
          lcd.print("Vazia");
        }else{
          lcd.print("Com carro");
        }
     }
     if(bdisplay==1){
        lcd.setCursor(0,0);
        lcd.print("Porao");
        lcd.setCursor(0,1);
        if(digitalRead(pir)==1){
          lcd.print("Ha' gente");
        }else{
          lcd.print("Ninguem aqui");
        }
     }
     if(bdisplay==2){
        lcd.setCursor(0,0);
        lcd.print("Portao");
        lcd.setCursor(0,1);
        if(k==0){
          lcd.print("Fechado");
        }
        if(k==1){
          lcd.print("Abrindo");
        }
        if(k==2){
          lcd.print("Fechando");
        }
        if(k==3){
          lcd.print("Aberto");
        }
     }
  }
  
  if(m-serial>1000){
    Serial.println(cm);
    Serial.print("cm");
    Serial.println(k);
    serial=m;
  }//Serial.println(k);
    Serial.println(cm);
    Serial.print("cm");
  
    /*if (m-rfid>10000){
    rfid=m;
      Serial.println("ID:");
      if(getID()==1){
      for (i = 0; i < mfrc522.uid.size; i++) 
      {
         //Serial.print(mfrc522.uid.uidByte[i]);
         //Serial.print(" ");
         id.concat(String(mfrc522.uid.uidByte[i],HEX));
         mfrc522.uid.uidByte[i]='\0';
       }
      }
       Serial.print(id);
       //delay(2000);
    }
    //Serial.print(id);
    if (id == "96f0a4ac"){
        //Serial.print("ENTREI");
        tmotor=m;
        k=1;
        id="";
    }
    else if (id != "0000" || id != ""){
        tmotor=m;
        k=5;
    }else{Serial.print("TAG ERRADA");}*/

    /*DateTime now = rtc.now(); //CHAMADA DE FUNÇÃO
    Serial.print("Data: "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.print(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
    Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
    Serial.print(" / Dia: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(diaSemana[now.dayOfTheWeek()]); //IMPRIME NO MONITOR SERIAL O DIA
    Serial.print(" / Horas: "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
    Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
    Serial.print(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS
    Serial.println(); //QUEBRA DE LINHA NA SERIAL
    delay(1000); //INTERVALO DE 1 SEGUNDO*/
       
}//loop end
