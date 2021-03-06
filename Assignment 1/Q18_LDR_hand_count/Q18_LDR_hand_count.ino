#include <LiquidCrystal.h>

int count = 0;

LiquidCrystal lcd(2,3,4,8,12,13);

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop(){
  
  long int main_time = millis();
  if(main_time - millis() <= 5000){
    if(analogRead(A3)> 1000)
      count++;
    delay(100);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(count); 
   Serial.println(count);
  }
  else {
    count = 0;
    exit(0);
  }
}
