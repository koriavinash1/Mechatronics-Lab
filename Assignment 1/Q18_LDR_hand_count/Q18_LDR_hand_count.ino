#include <LiquidCrystal.h>

int count = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop(){
  long int main_time = millis();
  if(main_time - millis() <= 5000){
    if(analogRead(A3)> 300)
      count++;
    delay(100);
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print(count);    
    count = 0;
    exit();
  }
}
