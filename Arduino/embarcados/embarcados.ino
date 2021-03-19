#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <stdlib.h>
#include "RTClib.h"
#include "SoftwareSerial.h"
SoftwareSerial bluetooth(2, 3); //TX, RX (Bluetooth)

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

const int stepsPerRevolution = 64;  // change this to fit the number of steps per revolution
// for your motor

//PINS################################################################
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
RTC_DS3231 rtc;

LiquidCrystal lcd(20, 21, 22, 23, 24, 25, 26, 27, 28, 29);

// motor
Stepper myStepper(stepsPerRevolution, 42, 43, 44, 45);

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
long timetraveled=0;
long stopb=0;
int stopbuzzer=0;
float lastd=0;
int lockerbuzzer=0;

//motor
long tmotor=0;
int gate=35;
int error=0;

//lcd
int buttonlcd=34;
int bdisplay=0;
int lastButtonState=0;
unsigned long lastDebounceTime=0;
unsigned int debounceDelay=50;
int buttonState=0;

//SETUP
void setup() {
  Serial.begin(9600);   // Inicia a serial
  bluetooth.begin(9600);
  //rtc
  rtc.begin();
  
  //rfid
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522  
  

  //stepper
  myStepper.setSpeed(60);
  pinMode(gate, OUTPUT);
  
  //ultrassom/buzzer
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  
  //PIR
  pinMode(lamp, OUTPUT);
  pinMode(pir, INPUT);

  //lcd
  lcd.begin(16, 2); // Define o número de colunas e linhas do display LCD usado.*/
  pinMode(gate, INPUT); //LCD mode
}

void debounce() {
  int reading = digitalRead(buttonlcd);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        bdisplay++;
        if(bdisplay==5){
          bdisplay=0;
        }
      }
    }
  }
  lastButtonState = reading;
}

byte readCard[4];
int getID() {
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return 0;
  }
  // There are Mifare PICCs which have 4 byte or 7 byte UID care if you use 7 byte PICC
  // I think we should assume every PICC as they have 4 byte UID
  // Until we support 7 byte PICCs
  Serial.println(F("Scanned PICC's UID:"));
  mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}
int aux=0;
String id="";
//LOOP
void loop() {
Serial.println("banana");
  //RFID
  long m=millis();
  
  Serial.println("ID:");
  if(getID()==1 or getID()==0){
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       Serial.print(mfrc522.uid.uidByte[i]);
       Serial.print(" ");
       id.concat(String(mfrc522.uid.uidByte[i],HEX));
       mfrc522.uid.uidByte[i]='\0';
    }
  }
  
  if (id == "9b355aa"){
      tmotor=millis();
      k=1;
      id="";
  }
  else if (id != "0000" || id != ""){
      tmotor=millis();
      k=5;
  }
  
  if(k==1){
    myStepper.step(stepsPerRevolution);
  }
  else if(k==2){
    myStepper.step(-stepsPerRevolution);
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
  
  if(k==5 && tmotor%1001==1000 && error<=4){
    aux=!aux;
    digitalWrite(lamp, aux);
    error++;
  }
  if(error==4){
    error=0;
  }
  
  //pir
  if(digitalRead(pir)==1){
    Serial.println("SOMEONE IS HERE");
    digitalWrite(lamp, HIGH);
  }
  else{
    digitalWrite(lamp, LOW);
  }
  
  //ultrassom/buzzer
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  timetraveled = pulseIn(echoPin, HIGH);
  cm = (timetraveled/2)*0.0343;
  Serial.println(cm);
  Serial.print("cm");
  if(stopbuzzer==0){
    if(cm<5 && cm>4 && millis()-time_us_d>500){
        Serial.println("a");
        time_us_d=millis();
        digitalWrite (buzzer, HIGH) ;
        delayMicroseconds(200) ;
        digitalWrite (buzzer, LOW) ;
        delayMicroseconds(200) ;
      Serial.println("CARALHO");
     }
    else if(cm<4 && cm>3 && millis()-time_us_d>250){
      Serial.println("b");
        time_us_d=millis();
        digitalWrite (buzzer, HIGH) ;
        delayMicroseconds(200) ;
        digitalWrite (buzzer, LOW) ;
        delayMicroseconds(200) ;
      Serial.println("BANANIHA");
     }
    else if(cm<3 && cm>2 && millis()-time_us_d>125){
        time_us_d=millis();
        digitalWrite (buzzer, HIGH) ;
        delayMicroseconds(200) ;
        digitalWrite (buzzer, LOW) ;
        delayMicroseconds(200) ;
     }
    else if(cm<2.50 && cm>1){
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
  if(cm<lastd+0.4 && cm>lastd-0.4 && lockerbuzzer==4){
    stopbuzzer=1;
    Serial.println("hi");
    lockerbuzzer=0;
  }
  if(cm<lastd-0.4){
    stopbuzzer=0;
  }

  //lcd
   debounce();
   if(bdisplay==0){
      lcd.setCursor(0,0);
      lcd.print("Garagem");
      lcd.setCursor(0,1);
      if(cm>15){
        lcd.print("Vazia");
      }else{
        lcd.print("Com carro");
      }
   }
   if(bdisplay==1){
      lcd.setCursor(0,0);
      lcd.print("Porão");
      lcd.setCursor(0,1);
      if(pir==1){
        lcd.print("Ha' gente");
      }else{
        lcd.print("Ninguem aqui");
      }
   }
   if(bdisplay==2){
      lcd.setCursor(0,0);
      lcd.print("Portão");
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
    //if (bluetooth.available() > 0)
    //bluetooth.println("LED: ON");
}
