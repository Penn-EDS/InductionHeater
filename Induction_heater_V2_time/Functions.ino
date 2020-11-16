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
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Time in Seconds : ");
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
    lcd.print("Time in Seconds : ");
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
    lcd.print("Time in Seconds : ");
    lcd.setCursor(0,1);
    lcd.print(timeon);
    lcd.setCursor(0,2);
    lcd.print("Press: A(+) , B(-)");
    lcd.setCursor(0,3);
    lcd.print("Press C to Continue");
  }
}
timeonmillis=timeon*1000;
delay(300);
}
