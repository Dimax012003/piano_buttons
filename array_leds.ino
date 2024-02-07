#include <LCD_I2C.h>

#include <BfButton.h>
#include <BfButtonManager.h>
LCD_I2C lcd(0x27,16,2);
int butpin=A2;
int clk=4;
int dt=3;
int k=0;
int button1=2;
int button2=1;
int array[]={6,7,8,9,10,11,12,13};
int notes[]={523,587,660,698,784,880,988,1046};
String cnotes[]={"C/5","D/5","E/5","F/5","G/5","A/5","B/5","C/6"};
int aState;
int aLastState;
int counter=0;
int buzzer=5;
BfButton btn(BfButton::STANDALONE_DIGITAL,butpin,true,LOW);
void presshandler(BfButton *btn,BfButton::press_pattern_t pattern){
switch(pattern){
case BfButton::SINGLE_PRESS:
  
  Serial.print("Single push");
  Serial.print(counter);
  for(int i=0;i<counter;i++){
     digitalWrite(array[i],HIGH);
  }
  noTone(buzzer);
  notes[k]=notes[k]+10;
  delay(10);
  
break;
case BfButton::DOUBLE_PRESS:
  
  Serial.print("Single push");
  Serial.print(counter);
  for(int i=0;i<counter;i++){
     digitalWrite(array[i],HIGH);
  }
  noTone(buzzer);
  notes[k]=notes[k]-10;
  delay(10);
  
break;
}
}
void setup() {
  // put your setup code here, to run once:
for(int i=0;i<8;i++){
  pinMode(array[i],INPUT);

}
pinMode(buzzer,OUTPUT);
pinMode(clk,INPUT);
pinMode(dt,INPUT);
pinMode(button1,INPUT);
pinMode(button2,INPUT);
btn.onPress(presshandler).onDoublePress(presshandler);
lcd.backlight();
lcd.begin();
aLastState=digitalRead(clk);
Serial.begin(115200);
}
int pin1=0;
int pin2=0;
int pushed=0;
void loop() {
  // put your main code here, to run repeatedly:
pin2=digitalRead(button1);
pin1=digitalRead(button2);
if(pin1==1){
  pushed=1;
}
if(pin2==1){
  pushed=0;
}
Serial.print(pushed);
if(pushed==1){
int pin=0;

for(int j=0;j<8;j++){
  pin=digitalRead(array[j]);
    if(pin==1){
      lcd.clear();
      tone(buzzer,notes[j],200);
      k=j;
    }
}
 btn.read();
  aState=digitalRead(clk);
if(aState!=aLastState){
  if(digitalRead(dt)!=aState){

      
      notes[k]=notes[k]+1;
  }
  else{
        
      notes[k]=notes[k]-1;
  }

Serial.print(counter);
}
aLastState=aState;

lcd.setCursor(1,0);
lcd.print(cnotes[k]);
lcd.setCursor(1,1);
lcd.print(notes[k]);
}



else if(pushed==0){
  
  lcd.setCursor(0,0);
  lcd.print("System Closed");
  digitalWrite(buzzer,LOW);
  noTone(buzzer);  
  for(int i=0;i<8;i++){
    digitalWrite(array[i],LOW);   
  }
}
Serial.print(pushed);
}
/*
  btn.read();
  aState=digitalRead(clk);
if(aState!=aLastState){
  if(digitalRead(dt)!=aState){

      counter++;

  }
  else{
      counter--;  
  }

  if(counter>7){
    counter=0;
  }
  if(counter<0){
    counter=7;
  }
Serial.print(counter);
}
aLastState=aState;

digitalWrite(array[counter],HIGH);
tone(buzzer,notes[counter]);

if(counter!=0){for(int i=0;i<8;i++){
  if(i!=counter){
  digitalWrite(array[i],LOW);
  }
}
}
else {for(int i=0;i<8;i++){
  
  digitalWrite(array[i],HIGH);
  
}
} 
lcd.clear();
lcd.setCursor(0,0);
lcd.print(cnotes[counter]);
*/