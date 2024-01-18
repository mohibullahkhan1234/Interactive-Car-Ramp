//car main controller

#include <SoftwareSerial.h>

const int rxPin1 = 0; //
const int txPin1 = 6; // on IC it is pin 9(verified)
const int rxPin2 = 1; //
const int txPin2 = 7; // on IC it is pin 13(verified)
const int rxPin3 = 2; //
const int txPin3 = 8   ; // on IC it is pin 14(verified)

SoftwareSerial mySerial1(rxPin1, txPin1); // RX, TX
SoftwareSerial mySerial2(rxPin2, txPin2); // RX, TX
SoftwareSerial mySerial3(rxPin3, txPin3); // RX, TX

int sen1 = 3;// This was pin number 9 (on IC : pin 1)(verified)
int sen2 = 4;// This was pin number 10 (on IC : pin 10) (verifeid)
int sen3 = 5;// This was pin number 5 (on IC : pin 11) (verified)

unsigned long sen1time;
unsigned long sen2time;
unsigned long sen3time;
unsigned long endtime;
 
boolean sen1e = false;
boolean sen2e = false;
boolean sen3e = false;
boolean raceended = false;
boolean datasent= false;

int sen1pos=0;
int sen2pos=0;
int sen3pos=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    mySerial1.begin(9600);
    mySerial2.begin(9600);
    mySerial3.begin(9600);
  pinMode(sen1, INPUT_PULLUP);
  pinMode(sen2, INPUT_PULLUP);
  pinMode(sen3, INPUT_PULLUP);
digitalWrite(sen1,HIGH);
digitalWrite(sen2,HIGH);
digitalWrite(sen3,HIGH);
}
int tempsen1;
int tempsen2;
int tempsen3;
void loop() {
  // put your main code here, to run repeatedly:
  if(!sen1e){
    tempsen1 = digitalRead(sen1);
  if (tempsen1 == LOW )
  {
    sen1time = millis();
   Serial.print("SEN 1 TIME: ");
  Serial.println(sen1time);
    sen1e = true;
  }}
  if(!sen2e){
    tempsen2 = digitalRead(sen2);
  if (tempsen2 == LOW )
  {
    sen2time = millis();
    Serial.print("SEN 2 TIME: ");
  Serial.println(sen2time);
    sen2e = true;
  }}
  if(!sen3e){
    tempsen3 = digitalRead(sen3);
  if (digitalRead(sen3) == LOW )
  {
    sen3time = millis();
     Serial.print("SEN 3 TIME: ");
  Serial.println(sen3time);
    sen3e = true;
  }}
  
  if (sen1e && sen2e && sen3e && !raceended)
  {
    endtime = millis();
    raceended = true;

  Serial.print("SEN END TIME: ");
  Serial.println(endtime);
   Serial.println();

  if(sen1time<sen2time && sen1time<sen3time && sen2time<sen3time && raceended)
  {
    sen1pos=1;
    sen2pos=2;
    sen3pos=3;
    }
  if(sen1time<sen2time && sen1time<sen3time && sen2time>sen3time && raceended)
  {
    sen1pos=1;
    sen2pos=3;
    sen3pos=2;
    }
    
  if(sen2time<sen1time && sen2time<sen3time && sen1time<sen3time && raceended)
  {
    sen1pos=2;
    sen2pos=1;
    sen3pos=3;
    }
        
  if(sen2time<sen1time && sen2time<sen3time && sen1time>sen3time && raceended)
  {
    sen1pos=3;
    sen2pos=1;
    sen3pos=2;
    }
 if(sen3time<sen1time && sen3time<sen2time && sen1time<sen2time && raceended)
  {
    sen1pos=2;
    sen2pos=3;
    sen3pos=1;
    }
        
  if(sen3time<sen1time && sen3time<sen2time && sen1time>sen2time && raceended)
  {
    sen1pos=3;
    sen2pos=2;
    sen3pos=1;
    }
    Serial.print("SEN 1 POS: ");
    Serial.println(sen1pos);
    Serial.print("SEN 2 POS: ");
    Serial.println(sen2pos);
    Serial.print("SEN 3 POS: ");
    Serial.println(sen3pos);
     Serial.println();
     mySerial1.print(sen1pos);
     delay(100);
     mySerial2.print(sen2pos);
     delay(100);
     mySerial3.print(sen3pos);
     delay(100);
     Serial.println("DATA SENT");
     datasent=true;
}
  

  
  if(tempsen1 == HIGH && tempsen2 == HIGH && tempsen3 == HIGH)
{
  sen1e = false;
   sen2e = false;
     sen3e = false;
   raceended = false;
   datasent=false;
   Serial.println("RACE NOT ENDED");
   sen1pos=0;
   sen2pos=0;
   sen3pos=0;
   sen1time=0;
   sen2time=0;
   sen3time=0;
  }
}
