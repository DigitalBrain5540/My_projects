#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,2);

void setup(){
  pinMode(15, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  //lcd.setCursor(0,1);
}

void loop(){
  Serial.println(touchRead(15));
  lcd.print(touchRead(15));
  lcd.clear();

}
