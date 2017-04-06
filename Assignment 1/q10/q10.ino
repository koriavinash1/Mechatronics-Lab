#include<LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,8,12,13);

void setup() {
 
  lcd.begin(16, 2); // 16x2 lcd
 
  lcd.print("abcd");
}

void loop() {
  
  lcd.setCursor(0, 1);
  
}

