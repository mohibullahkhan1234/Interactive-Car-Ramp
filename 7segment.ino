   //car tracks code

#include <SoftwareSerial.h>
const int rxPin = 16; //A2 pin 17 on IC
const int txPin = 17; //A3
SoftwareSerial mySerial1(rxPin, txPin); // RX, TX

const int dataPin = 7;    // data pin for shift registers     DS  last digit pin  Digital
const int latchPin = 5;   // latch pin for shift registers    STCP  PWM
const int clockPin = 6;   // clock pin for shift registers    SHCP  PWM

int digits[4] = {0, 0, 0, 0};  // array to store individual digits of count


const int startPin = 9; // Pin for the start sensor
const int endPin = 10; // Pin for the end sensor

unsigned long startTime = 0; // Variable to hold the start time
unsigned long endTime = 0; // Variable to hold the end time
unsigned long timeelapsed = 0; 
bool raceStarted = false; // Flag to track whether the race has started or not

int receivedMillis;

void setup() {
  Serial.begin(9600); // Initialize serial communication
   mySerial1.begin(9600);
  pinMode(startPin, INPUT_PULLUP); // Configure start sensor as input
  pinMode(endPin, INPUT_PULLUP); // Configure end sensor as input
 pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  digits[0] = 0;
    digits[1] = 0;
    digits[2] = 0;
    digits[3] = 0;
     updateDisplay();

}

int counter = 0;
void loop() {
  
  // Check if the start sensor has been triggered
  if (digitalRead(startPin) == LOW && !raceStarted) {
    while(1){
Serial.println(digitalRead(startPin));
if(digitalRead(startPin) == HIGH) counter++;
Serial.print("counter : ");
Serial.println(counter);
if(counter > 10  ) break;
        }
        raceStarted = true;
    startTime = millis();
    Serial.println("Race started");
    }

  // Check if the end sensor has been triggered
  if (digitalRead(endPin) == LOW && raceStarted) {
    raceStarted = false;
    endTime = millis();
    Serial.print("Race ended. Time: ");
    unsigned long endTimes=endTime - startTime;
    Serial.print(endTimes);
    Serial.println(" ms");
    
   while(receivedMillis<1)
{
 // Serial.println("WHILE"); 
 if(mySerial1.available()>0)
 {
    receivedMillis = mySerial1.parseInt(); // read the millis value from software serial
    Serial.print("DATA: ");
    Serial.println(receivedMillis); 

if(receivedMillis==1)
{
    Serial.println("FIRST");
 digits[0] = 11;
    digits[1] = 11;
    digits[2] = 11;
    digits[3] =11;
    updateDisplay();
  delay(2000);

  digits[0] = 11;
    digits[1] = 12;
    digits[2] = 5;
    digits[3] =1;

    updateDisplay();
  }
  if(receivedMillis==2)
{
  Serial.println("SECOND");
   digits[0] = 11;
    digits[1] = 11;
    digits[2] = 11;
    digits[3] =11;
    updateDisplay();
  delay(2000);
    digits[0] = 11;
    digits[1] = 14;
    digits[2] = 15;
    digits[3] =2;

    updateDisplay();
  }
  if(receivedMillis==3)
{
  Serial.println("THIRD");
   digits[0] = 11;
    digits[1] = 11;
    digits[2] = 11;
    digits[3] =11;
    updateDisplay();
  delay(2000);
   digits[0] = 11;
    digits[1] = 14;
    digits[2] = 13;
    digits[3] =3;

    updateDisplay();
  }

  }}}
if(raceStarted)
{
  timeelapsed=millis();
 unsigned long timeelapseds=timeelapsed-startTime;
  Serial.println(timeelapseds);

 digits[0] = (timeelapseds / 100) % 10;
    digits[1] = (timeelapseds / 1000) % 10;
    digits[2] = (timeelapseds / 10000) % 10;
    digits[3] = (timeelapseds/ 100000) % 10;

    // update the display
    updateDisplay();
  
  }
  receivedMillis=0;
}



void updateDisplay() {
 
digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, digitToSegment(digits[0]));
    shiftOut(dataPin, clockPin, LSBFIRST, digitToSegment(digits[1]));
    shiftOut(dataPin, clockPin, LSBFIRST, digitToSegment(digits[2]));
    shiftOut(dataPin, clockPin, LSBFIRST, digitToSegment(digits[3]));
    digitalWrite(latchPin, HIGH); 
    
}

byte digitToSegment(int digit) {
  // return the 7-segment code for the given digit
  switch (digit) {
    case 0:
      return 1;
    case 1:
      return 79;
    case 2:
      return 18;
    case 3:
      return 6;
    case 4:
      return 76;
    case 5:
      return 36;
    case 6:
      return 32;
    case 7:
      return 15;
    case 8:
      return 0;
    case 9:
      return 4;
   case 11: //alloff
      return 255;
    case 12:
      return 112;//t
    case 13:
      return 122;//r
    case 14:
      return 66;//d
    case 15:
      return 106;//n
  }
}
/*
//1st
digits[0] = 11;
    digits[1] = 12;
    digits[2] = 5;
    digits[3] =1;
    updateDisplay();

//2nd
    digits[0] = 11;
    digits[1] = 14;
    digits[2] = 15;
    digits[3] =2;
    updateDisplay();
   
//3rd
    digits[0] = 11;
    digits[1] = 14;
    digits[2] = 13;
    digits[3] =3;
    updateDisplay();
    
      */
