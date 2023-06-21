/*
Saurabh Salvi
ME22B1033
TAD Assignment - Misc. Assignment
*/

#include <Servo.h>

#include <LiquidCrystal.h>

const int rs = 13, enLCD = 11, d4 = 4, d5 = 5, d6 = 7, d7 = 2;
LiquidCrystal lcd(rs, enLCD, d4, d5, d6, d7);

Servo rudder;
Servo aeliron;

int potValProp; //Propeller
int potValRud;
int potValAeli;
int pos;
int pos1;
int in3 = 9;    // for DC motor control
int in4 = 8;
int en = 10; // enable pin

void setup()
{
   
  rudder.attach(6);
  aeliron.attach(3);
  
  pinMode(en, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A3, INPUT);
  pinMode(A5, INPUT);
  
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("TAD Club");
  delay(3000);
  for (int Counter = 0; Counter < 16; Counter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(150);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RudderAngle:");
  // print the number of seconds since reset:
}

void loop()
{
  int m= pos-90;
  // lcd.setCursor(0, 1);
  // + ACW
  //lcd.print(m);
  if(m>=0){
    lcd.setCursor(0, 1);
  	lcd.print(m);
    lcd.setCursor(3, 1);
    lcd.print("deg");
    lcd.setCursor(7, 1);
    lcd.print("ACW");
  }
  else if(m<0){
    lcd.setCursor(0, 1);
  	lcd.print(-m);
    lcd.setCursor(3, 1);
    lcd.print("deg");
    lcd.setCursor(7, 1);
    lcd.print("CW");
   
  }
  
  /*
  On Serial monitor
  +ve angle implies ACW
  -ve angle imples CW
  
  */
  //---------------------------------------------------------
  //**for rudder servo**
  potValRud = analogRead(A0);
  
  
  pos = map(potValRud, 0, 1023, 0, 180);
  Serial.print("Angle by rudder : ");
  
  Serial.println(m);

  //Problem is coming regarding the continuous looping of 
  //if(pos>=90)
  if(pos >= 90){
  for(int i = 90; i<=pos; i++){
  	rudder.write(i);
    delay(100);
    
  }
  }
  //perfect below code !!
  else if(pos < 90){
    for(int i = 90; i>=pos; i--){
    	rudder.write(pos);
      	delay(100);
      }
  }
  //-------------------------------------------------------
  //**for aeliron servo**
  potValAeli = analogRead(A1);
  
  
  pos1 = map(potValAeli, 0, 1023, 0, 180);
  Serial.print("Angle by aeliron : ");
  Serial.println(pos1-90);

  //Problem is coming regarding the continuous looping of 
  //if(pos>=90)
  if(pos1 >= 90){
  for(int i = 90; i<=pos1; i++){
  	aeliron.write(i);
    delay(100);
    
  }
  }
  //perfect below code !!
  else if(pos1 < 90){
    for(int i = 90; i>=pos1; i--){
    	aeliron.write(pos1);
      	delay(100);
      
    }
  }
  //----------------------------------------------------------
  //**for propeller**
  
  potValProp = analogRead(A3);
  int final = map(potValProp, 0, 1023, 0, 255);
  //if (final < 127){
  
  analogWrite(en, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(3000);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  //}
  
  
 /* 
  else if (final>127){
  
    
  analogWrite(en, potValProp/4);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  
  }
  */
 
  //-----------------------------------------------------------
  
}