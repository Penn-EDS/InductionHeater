void SupplyVoltage(){
  while((analogRead(OutvalSup)*0.0644219)<40 || (analogRead(OutvalSup)*0.0644219)>54){
  digitalWrite(Relay48V, LOW);
  Serial.println("Voltage Low or High");
  if(v==0){
    v=1;
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Relay OFF");
    lcd.setCursor(0,2);
    lcd.print("Voltage Out Of Range");
  }
  delay(5000);
  
 }
 if(v==1){
    v=0;
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Started");
  lcd.setCursor(0,1);
  lcd.print("Time ON Sec:");
  lcd.print(timeon);
    
 }
}

void SetCurrent(){
  
  delay(300);
  while(digitalRead(ButtonC)==HIGH){
    delay(100);
  if(digitalRead(ButtonA)==LOW){
    currentpercent=currentpercent+1;
    if(currentpercent>=52){
      currentpercent=52;
    }
    pwmvalue=map(currentpercent,10,52,57,237);
    analogWrite(PWM,pwmvalue);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Current: ");
    lcd.print(currentpercent);
  }
    
  if(digitalRead(ButtonB)==LOW){
    currentpercent=currentpercent-1;
    if(currentpercent<=10){
      currentpercent=10;
    }
    pwmvalue=map(currentpercent,10,52,57,237);
    analogWrite(PWM,pwmvalue);
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Current: ");
    lcd.print(currentpercent);
  }
}

delay(300);
  
}

void SetTime(){
  //
  //Set time on
  //
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time ON in Sec:");
    lcd.setCursor(0,1);
    lcd.print(timeon);
    lcd.setCursor(0,2);
    lcd.print("Press: A(+) , B(-)");
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
    
  delay(300);
  while(digitalRead(ButtonC)==HIGH){
    delay(20);
  if(digitalRead(ButtonA)==LOW){
    timeon=timeon+1;
    if(timeon>=90){
      timeon=90;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time ON in Seconds:");
    lcd.setCursor(0,1);
    lcd.print(timeon);
    lcd.setCursor(0,2);
    lcd.print("Press: A(+) , B(-)");
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
  }
    
  if(digitalRead(ButtonB)==LOW){
   timeon=timeon-1;
   if(timeon<=1){
      timeon=1;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time ON in Seconds:");
    lcd.setCursor(0,1);
    lcd.print(timeon);
    lcd.setCursor(0,2);
    lcd.print("Press: A(+) , B(-)");
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
  }
}

while(digitalRead(ButtonC)==LOW){} //Crude debouncing
delay(200);
//
//Set time off
//
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time OFF in Sec:");
    lcd.setCursor(0,1);
    lcd.print(timeoff);
    lcd.setCursor(0,2);
    lcd.print("Press: A(+) , B(-)");
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
    
  while(digitalRead(ButtonC)==HIGH){
    delay(20);
  if(digitalRead(ButtonA)==LOW){
    timeoff=timeoff + 1;
    if(timeoff>=30){  //Set maximum time coil will be off
      timeoff=30;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time OFF in Seconds:");
    lcd.setCursor(0,1);
    lcd.print(timeoff);
    lcd.setCursor(0,2);
    lcd.print("Press: A(+) , B(-)");
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
  }
    
  if(digitalRead(ButtonB)==LOW){
   timeoff=timeoff-1;
   if(timeoff <= 15){ //Set minimum time coil will be off
      timeoff = 15;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time OFF in Seconds:");
    lcd.setCursor(0,1);
    lcd.print(timeoff);
    lcd.setCursor(0,2);
    lcd.print("Press: A(+) , B(-)");
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
  }
}

while(digitalRead(ButtonC)==LOW){} //Crude Debouncing
delay(200);
//
//Set Cycles
//
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cycles:");
    lcd.setCursor(0,1);
    lcd.print(cyclesOn);
    lcd.setCursor(0,2);
    lcd.print("Press: A(+) , B(-)");
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
    
  while(digitalRead(ButtonC)==HIGH){
    delay(20);
  if(digitalRead(ButtonA)==LOW){
    cyclesOn = cyclesOn + 1;
    if(cyclesOn >= 5){  //Set maximum number of cycles
      cyclesOn = 5;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cycles:");
    lcd.setCursor(0,1);
    lcd.print(cyclesOn);
    lcd.setCursor(0,2);
    lcd.print("Press: A(+) , B(-)");
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
  }
    
  if(digitalRead(ButtonB)==LOW){
   cyclesOn = cyclesOn - 1;
   if(cyclesOn <= 1){ //Set minimum number of cycles
      cyclesOn = 1;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cycles:");
    lcd.setCursor(0,1);
    lcd.print(cyclesOn);
    lcd.setCursor(0,2);
    lcd.print("Press: A(+) , B(-)");
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
  }
}

EEPROM.update(addressON, timeon);
EEPROM.update(addressOFF, timeoff);
EEPROM.update(addressCycles, cyclesOn);

timeonmillis = timeon * 1000;
timeoffmillis = timeoff * 1000;
totalTimeMin = ((timeon + timeoff) * cyclesOn) / 60;
totalTimeSec = ((timeon + timeoff) * cyclesOn) - (totalTimeMin * 60);

while(digitalRead(ButtonC)==LOW){} //Crude Debouncing
delay(300);
}

void elapsedTimeCode(){
  elapsedMin = timeonsec / 60;
  elapsedSec = timeonsec - (elapsedMin*60);
  lcd.print(elapsedMin);
  lcd.setCursor(2,2);
  lcd.print("Min");
  lcd.setCursor(6,2);
  lcd.print(elapsedSec);
  lcd.setCursor(9,2);
  lcd.print("Sec");
}
