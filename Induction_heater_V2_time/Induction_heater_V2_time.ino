// This code control the current of power supply "----" 
#define ButtonA 9
#define ButtonB 8
#define ButtonC 7
#define ButtonD 6
#define OutvalOpam A1  //Output of Opam 0 to 5V. This input will be measure to ensure that the value are the correct one. 
#define OutvalSup A0   // value of power supply output UHP-2500-48
#define PWM 10  
#define Relay48V 2

         #include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);


float VOutOpam = 0.0;         // variable to store the read value
float VOutSup = 0.0;
int currentVal=0;
int val=0;
int maxcurrent= 160; // 160 = to 35.00 A
int currentpercent=20;
int v=0;
unsigned long timeon=30;
unsigned long timeonmillis=0;
unsigned long timeonsec=0;
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
  
Top:  
//  val=map(currentVal,0,"max current here",0,255);
//  analogWrite(PWM, val);   // analogWrite values from 0 to 255

// set up current %
//SetCurrent();
SetTime();
here:
lcd.clear();
lcd.setCursor(0,0); 
lcd.print("Time ON Sec:");
lcd.setCursor(0,1);
lcd.print(timeon);
lcd.setCursor(0,2);
lcd.print("Press C to Start");
lcd.setCursor(0,3);
lcd.print("Press D Change Time");
while(1){

 if(digitalRead(ButtonC)==LOW){
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Started");
  lcd.setCursor(0,1);
  lcd.print("Elapsed Time Sec:");
  lcd.setCursor(0,2);
  //lcd.print(timeon);
  lcd.setCursor(0,3);
  lcd.print("Press D to Cancel");
  
  Time=millis();
  timenow=millis()-Time+1000;
  while((millis()-Time)<timeonmillis){
   digitalWrite(Relay48V, HIGH);
   SupplyVoltage();
   if(millis()-Time>=timenow){
    timenow=millis()-Time+1000;
     lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("Started");
     lcd.setCursor(0,1);
     lcd.print("Elapsed Time Sec:");
     lcd.setCursor(0,2);
     timeonsec=((millis()-Time)/1000);
     lcd.print(timeonsec);
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
    lcd.print("Elapsed Time Sec:");
    lcd.setCursor(0,2);
    lcd.print(timeonsec);
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
    while(digitalRead(ButtonC)==HIGH){
    }
    delay(500);
    goto here;
   }
  }
  
  digitalWrite(Relay48V, LOW);
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Completed");
  lcd.setCursor(0,1);
  lcd.print("Time ON Sec:");
  lcd.setCursor(0,2);
  lcd.print(timeon);
  delay(1000);
  goto here;
  
 }
 if(digitalRead(ButtonD)==LOW){
  goto Top;
 }
}
  
}
