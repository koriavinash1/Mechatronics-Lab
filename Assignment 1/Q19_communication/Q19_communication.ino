#include <LiquidCrystal.h>
String astr="",bstr="";

int a = 0, b = 0, c = 0;

String str = "";
boolean stringComplete = false; 

LiquidCrystal lcd(2,3,4,8,12,13);
void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  str.reserve(200);
}

void loop(){
  serialEvent();
  if (stringComplete){
    for(int i = 0; i < str.length(); i++){
      if(str[i] == 'a')
        a = i;
      if(str[i] == 'b')
        b = i;
      if(str[i] == 'c')
        c = i;
    }
    for(int j = a+1; j < b; j++)
      astr += str[j];
      
    for(int k = b+1; k < c; k++)
      bstr += str[k];
    str="";
    stringComplete = false;
  }
  Serial.print(astr + '\t');
  Serial.println(bstr);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(astr);
  lcd.setCursor(0,1);
  lcd.print(bstr);
  exit;
}

void serialEvent() {
  while (Serial.available()) {
    //Serial.println("A");
    char inChar = (char)Serial.read(); 
    str += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

