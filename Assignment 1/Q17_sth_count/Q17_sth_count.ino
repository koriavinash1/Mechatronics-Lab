#include <LiquidCrystal.h>

int count = 0;
int flag = 0;

LiquidCrystal lcd(2,3,4,8,12,13);

void setup(){
  pinMode(7, INPUT_PULLUP);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop(){  
  long int main_time = millis();
  //Serial.println(millis());
  if(main_time - millis() <= 5000){
    if(digitalRead(7) == LOW && flag == 0){
      count++;
      flag = 1;
    }
    else if(digitalRead(7) == HIGH)
      flag = 0;
    delay(100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(count); 
   Serial.println(count);
  }
  else {
       
    count = 0;
    exit(0);
  }
}
