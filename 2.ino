#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define pinY A1 

LiquidCrystal_I2C lcd(0x27,16,2);  
Servo motor;

void setup() {
  Serial.begin(9600);
  motor.writeMicroseconds(0);
  pinMode(pinY, INPUT);
  
  lcd.init(); 
  lcd.backlight();
  lcd.home();
  lcd.print("Welcome!");
  motor.attach(9);
  delay(1000);
}

void loop() {
  int percent;
  int val = analogRead(pinY);
  lcd.clear();
  lcd.home();
  lcd.setCursor(1, 0);
  if (val > 497){
    val = map(val, 497, 1023, 945, 1800);
    percent = map(val, 945, 1790, 0, 100);
    lcd.print("Speed:");
    if (percent==100)lcd.setCursor(9, 1);
    else {
      if(percent<10) lcd.setCursor(11, 1); 
      else lcd.setCursor(10, 1); 
    }
    lcd.print(percent);
    lcd.print("\x25");
    motor.writeMicroseconds(val);
    delay(100);
  }
  else 
  {
    lcd.print("Speed:");
    lcd.setCursor(11, 1);
    lcd.print(0);
    lcd.print("\x25");
    motor.writeMicroseconds(0);
  }
  delay(200);
}
