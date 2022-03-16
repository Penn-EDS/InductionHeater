// Purpose: This code control the current of power supply "----"
// This program can control the ON and OFF times of an induction heater and
// the total time of operation by means of number of cycles.
//
// Original Author: Alexander Santos (Nov 12, 2020 Build)
// Rev 1.1 Author: Pedro Quijano
// Date : March 16, 2022
//
// Rev 1.1: Enabled setting of ON and OFF times, and cycle number.
//          Values chosen are stored on the EEPROM
// Rev 1.0: Original Code (was before adopting version control)
//

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define ButtonA 9
#define ButtonB 8
#define ButtonC 7
#define ButtonD 6
#define OutvalOpam A1  //Output of Opam 0 to 5V. This input will be measure to ensure that the value are the correct one.
#define OutvalSup A0   // value of power supply output UHP-2500-48
#define PWM 10
#define Relay48V 2

//I2C pins declaration
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

int addressON = 0;  //Address for the EEPROM
int addressOFF = 1;
int addressCycles = 2;
float VOutOpam = 0.0;         // variable to store the read value
float VOutSup = 0.0;
int currentVal=0;
int val=0;
int maxcurrent= 160; // 160 = to 35.00 A
int currentpercent=20;
int v=0;
int timeon=8;
int timeoff = 5;
int cyclesOn = 2;
int cyclesRun = 0;
int totalTimeMin = 0;
int totalTimeSec = 0;
unsigned long timeonmillis=0;
unsigned long timeoffmillis=0;
unsigned long timeonsec=0;
unsigned long elapsedMin = 0;
unsigned long elapsedSec = 0;
unsigned long Time=0;
unsigned long timenow=1000;
int pwmvalue=0;

void setup() {
  Serial.begin(9600);
  pinMode(PWM, OUTPUT);  // sets the pin as output
  pinMode(ButtonA, INPUT_PULLUP);
  pinMode(ButtonB, INPUT_PULLUP);
  pinMode(ButtonC, INPUT_PULLUP);
  pinMode(ButtonD, INPUT_PULLUP);
  pinMode(OutvalOpam, INPUT);
  pinMode(OutvalSup, INPUT);
  pinMode(Relay48V, OUTPUT);
  analogWrite(PWM,maxcurrent);

  lcd.init();
  lcd.backlight();
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Current % : ");
//  lcd.print(currentpercent);
}


void loop() {

timeon = EEPROM.read(addressON);
timeoff = EEPROM.read(addressOFF);
cyclesOn = EEPROM.read(addressCycles);

Top:
//  val=map(currentVal,0,"max current here",0,255);
//  analogWrite(PWM, val);   // analogWrite values from 0 to 255

// set up current %
//SetCurrent();
SetTime();
here:
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Time ON:");
lcd.setCursor(8,0);
lcd.print(timeon);
lcd.setCursor(11,0);
lcd.print("Off:");
lcd.setCursor(15,0);
lcd.print(timeoff);
lcd.setCursor(0,1);
lcd.print("T-Time:");
lcd.setCursor(8,1);
lcd.print(totalTimeMin);
lcd.setCursor(10,1);
lcd.print("Min");
lcd.setCursor(14,1);
lcd.print(totalTimeSec);
lcd.setCursor(16,1);
lcd.print("Sec");
lcd.setCursor(0,2);
lcd.print("Press C to Start");
lcd.setCursor(0,3);
lcd.print("Press D Change Time");
while(1){

 if(digitalRead(ButtonC)==LOW){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Started ON");
  lcd.setCursor(0,1);
  lcd.print("Elapsed Time Sec:");
  lcd.setCursor(0,2);
  //lcd.print(timeon);
  lcd.setCursor(0,3);
  lcd.print("Press D to Cancel");

  for (cyclesRun = 0; cyclesRun < cyclesOn; cyclesRun++){

    Time=millis();
    timenow=millis()-Time+1000;

    while((millis()-Time)<timeonmillis){
      digitalWrite(Relay48V, HIGH);
      SupplyVoltage();

      if(millis()-Time>=timenow){
        timenow=millis()-Time+1000;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Started ON");
        lcd.setCursor(0,1);
        lcd.print("Elapsed Time:");
        lcd.setCursor(0,2);
        timeonsec=(((millis()-Time)/1000) + (timeon*cyclesRun) + (timeoff* (cyclesRun)));
        elapsedTimeCode();
        lcd.setCursor(0,3);
        lcd.print("Press D to Cancel");
        }

   /// update of the time when is running.
   if(digitalRead(ButtonD)==LOW){
      digitalWrite(Relay48V, LOW);
      timeonsec=((millis()-Time)/1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CANCELED");
      lcd.setCursor(0,1);
      lcd.print("Elapsed Time:");
      lcd.setCursor(0,2);
      timeonsec = timeonsec + timeon*(cyclesRun) + timeoff*(cyclesRun);
      elapsedTimeCode();
      lcd.setCursor(0,3);
      lcd.print("Press C to Continue");

    while(digitalRead(ButtonC)==HIGH){}

    delay(500);
    goto here;
    }
   }

   Time=millis();
   timenow=millis()-Time+1000;

   while((millis()-Time)<timeoffmillis){
    digitalWrite(Relay48V, LOW);
    SupplyVoltage();

    if(millis()-Time>=timenow){
        timenow=millis()-Time+1000;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Started OFF");
        lcd.setCursor(0,1);
        lcd.print("Elapsed Time:");
        lcd.setCursor(0,2);
        timeonsec=(((millis()-Time)/1000) + (timeon*(cyclesRun + 1)) + (timeoff*cyclesRun));
        elapsedTimeCode();
        lcd.setCursor(0,3);
        lcd.print("Press D to Cancel");
        }

   /// update of the time when is running.
   if(digitalRead(ButtonD)==LOW){
      digitalWrite(Relay48V, LOW);

      timeonsec=((millis()-Time)/1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CANCELED");
      lcd.setCursor(0,1);
      lcd.print("Elapsed Time:");
      lcd.setCursor(0,2);
      timeonsec = timeonsec + timeon*(cyclesRun) + timeoff*(cyclesRun - 1);
      elapsedTimeCode();
      lcd.setCursor(0,3);
      lcd.print("Press C to Continue");

    while(digitalRead(ButtonC)==HIGH){}

    delay(500);
    goto here;
    }
   }
  }

  digitalWrite(Relay48V, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Completed");
  lcd.setCursor(0,1);
  lcd.print("Total Time:");
  lcd.setCursor(0,2);
  timeonsec = timeon*cyclesRun + timeoff*cyclesRun;
  elapsedTimeCode();
  delay(2000);
  goto here;

 }
 if(digitalRead(ButtonD)==LOW){
   goto Top;
 }
}
}
