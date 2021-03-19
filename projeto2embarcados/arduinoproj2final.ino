String temp;
char k;
char a;
char b;
char c;

void setup() {
Serial.begin(9600);
Serial1.begin(9600);
Serial2.begin(9600);
temp[14]='\0';
}

void loop(){

  if(Serial1.available()){
   Serial.println("HI");
   //receive string from Serial1 until char 'k'
   temp=Serial1.readStringUntil('k');
   
   Serial.println(temp); 
   Serial.print(temp[4]);
   Serial.print(temp[5]);
   //control to trash strings
   if(temp[4]>=48 && temp[4]<=57)
      a=temp[4];
   if(temp[5]>=48 && temp[5]<=57)
      b=temp[5];
   if(temp[6]>=48 && temp[6]<=57)
      c=temp[6];
   Serial.print(a);
   Serial.print(b);  
   Serial.println();
  }
  
  if(Serial2.available()){
    if((char)Serial2.read()=='f'){
      Serial2.println();
      Serial.print("######");
      if(c=='1'){
        Serial.print("HIIII");
        if(a>=52) Serial2.print(" Exaustao maxima ativada ");
        else if(a<51 || (a==51 && b<53)) Serial2.print(" Exaustao desligada ");
      else Serial2.print(" Exaustao media ativada ");
      }
      else Serial2.print(" Exaustao desativada ");
      //send via Serial2 (bluetooth)
      Serial2.print(a);
      Serial2.print(b);
      Serial2.print("ºc");
    }
  }
  
   
}
