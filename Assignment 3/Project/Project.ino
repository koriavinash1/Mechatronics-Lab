#include <Servo.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,8,12,13);
Servo myservo;
int whitepatch_pos = 150, servo_position = whitepatch_pos, top_servo_pos = 0;
int LDR_whitepatch = 0;
int red = 11, green = 10, blue = 9, LDR = A2, Proximity = A1, electroMagnet = 7;
int color_LDR_val[] = {0,0,0,0,0,0,0,0,0,0,0,0};//LDR values
int color_PWM_val[] = {0,0,0,0,0,0,0,0,0,0,0,0};//0:red, 1:green, 2:blue // PWM values...
int color_ANGLE_val[] = {0,0,0,0,0,0,0,0,0,0,0,0};//Position angles
int base_servo = 6, top_servo = 5;
int number_color_patchs = 3;
int calib_done = false;
String taskString = "", calibrationString = ""; boolean stringComplete = false;

void setup(){
  Serial.begin(9600);
  pinMode(electroMagnet, OUTPUT);
  rotate_servo(base_servo, whitepatch_pos, 2000, 500);
  rotate_servo(top_servo, top_servo_pos, 2000, 500);  
  lcd.begin(16, 2);
  taskString.reserve(200);
  calibrationString.reserve(200);

  analogWrite(red, 255); analogWrite(green, 255); analogWrite(blue, 255); delay(500);
  LDR_whitepatch = analogRead(A2);
  analogWrite(red, 0); analogWrite(green, 0); analogWrite(blue, 0);
  lcd_print("WPatch_LDR:"+String(LDR_whitepatch), 1000);  
}

void loop(){
  if(!calib_done){
    serialEvent("calib");
    lcd_print("Calib mode?", 2000);
    while (Serial.available()) {
      Serial.println("HELLO");
      char inChar = (char)Serial.read();
      if(inChar == "m"){ ManualCalibrate(); if(millis()>20000) {calib_done = true; break;}}
      else if(inChar== "a"){ AutoCalibrate(); break;}
      else {lcd_print("Enter Proper Str", 1000); break;}
    }
  }  
  else if(calib_done){
    lcd_print("Pick up color?", 2000);
    while (Serial.available()) { 
      char inChar = (char)Serial.read();
      if(inChar == "r") taskString = "red";
      else if(inChar == "g") taskString = "green";
      else if(inChar == "b") taskString = "blue";
      else lcd_print("Enter Proper Str", 1000); 
      additionalTasks(); 
      break;
    }
  }
  lcd_print("Tasks Completed .....", 1000);
}

//additional functions...........
void ManualCalibrate(){
  for(int i=blue; i<=red; i++) { 
    analogWrite(i, 255); delay(200);
    color_LDR_val[i] = analogRead(LDR);
    lcd_print("R:"+String(color_LDR_val[red])+"G:"+String(color_LDR_val[green])+"B:"+String(color_LDR_val[blue]), 200);
    analogWrite(i, 0);
  }
}

void AutoCalibrate(){
  for(int i=blue; i<=red; i++){ initialCalibration(i); analogWrite(i, 0);}//Auto Calibrate...............
  lcd_print("calib to max.....", 2000);  
  int maxValue = find_max();
  Serial.println(maxValue);
  for(int i=blue; i<=red; i++){ calibrateToMax(maxValue, i); analogWrite(i, 0);}
  Serial.println("Calibrated Values................................");
  Serial.println("LDR Red:"+String(color_LDR_val[red])+"Green:"+String(color_LDR_val[green])+"Blue:"+String(color_LDR_val[blue])); 
  Serial.println("PWM Red:"+String(color_PWM_val[red])+"Green:"+String(color_PWM_val[green])+"Blue:"+String(color_PWM_val[blue]));

  lcd_print("finding color.....", 2000);
  while(servo_position >= 40){ servomotion();} //using efficient algo.....
  alternativeServoCode();//gen algo.....

  lcd_print("AR:"+String(color_ANGLE_val[red])+"G:"+String(color_ANGLE_val[green])+"B:"+String(color_ANGLE_val[blue]), 3000);
  Serial.println("Position Angles Red:"+String(color_ANGLE_val[red])+"Green:"+String(color_ANGLE_val[green])+"Blue:"+String(color_ANGLE_val[blue]));
  lcd_print("System Calibration Done...", 3000); 
  rotate_servo(base_servo, whitepatch_pos, 3000, 100);
  calib_done = true;
}

void additionalTasks(){
  if (taskString == "red"){ rotate_servo(base_servo,color_ANGLE_val[red], 3000, 100); pickObject(); }
  else if (taskString == "green"){ rotate_servo(base_servo ,color_ANGLE_val[green], 3000, 100); pickObject(); }
  else if (taskString == "blue"){ rotate_servo(base_servo, color_ANGLE_val[blue], 3000, 100); pickObject(); }
  else rotate_servo(base_servo, whitepatch_pos, 3000, 100);
  taskString = "";
  stringComplete = false;
}

void initialCalibration(int color){
  analogWrite(color, 255); delay(1000);
  color_LDR_val[color] = analogRead(LDR); color_PWM_val[color] = 255;
  lcd_print("R:"+String(color_LDR_val[red])+"G:"+String(color_LDR_val[green])+"B:"+String(color_LDR_val[blue]), 500);
}

int find_max(){
  if((color_LDR_val[red] > color_LDR_val[green]) && (color_LDR_val[red] > color_LDR_val[blue])) return color_LDR_val[red];
  else if((color_LDR_val[blue] > color_LDR_val[green])) return color_LDR_val[blue];
  else return color_LDR_val[green];
}

void calibrateToMax(int max_val, int color){
  int error = 10;  
  for(int i = 255; color_LDR_val[color] <= (max_val - error); i=i-3){
    analogWrite(color, i); delay(200);
    color_LDR_val[color] = analogRead(LDR);
    color_PWM_val[color] = i;
    lcd_multiline_print("IR:"+String(color_LDR_val[red])+"G:"+String(color_LDR_val[green])+"B:"+String(color_LDR_val[blue]), "CR:"+String(color_PWM_val[red])+"G:"+String(color_PWM_val[green])+"B:"+String(color_PWM_val[blue]), 100);
  }    
}

void servomotion(){
  int error = 25, angle_error = 20;
  analogWrite(red, 255); analogWrite(green, 255); analogWrite(blue, 255);
  for(int i = servo_position; i >= 40; i-=5){
    rotate_servo(base_servo, i, 500, 100);
    if((analogRead(LDR) >= LDR_whitepatch + error) && (i < (servo_position - angle_error ))){ servo_position = i; break; }
  }
  analogWrite(red, 0); analogWrite(green, 0); analogWrite(blue, 0);
  find_color();
}

void alternativeServoCode(){ for(int i=servo_position; i>= 0; i-=8){ servo_position = i; rotate_servo(base_servo, servo_position, 500, 100); find_color();}}

void find_color(){
  int error = 30;
  int t[] = {0,0,0,0,0,0,0,0,0,0,0,0};
  lcd_print("CR:"+String(color_PWM_val[red])+"G:"+String(color_PWM_val[green])+"B:"+String(color_PWM_val[blue]),2000);
  for(int i=blue; i<=red; i++){
    analogWrite(i, color_PWM_val[i]); delay(200);
    t[i] = analogRead(LDR);
    analogWrite(i, 0); delay(200);
  }

  if((t[red]<t[green])&&(t[red]<t[blue])){ lcd_print("Color = RED", 2000); color_ANGLE_val[red] = servo_position;}
  else if(t[green]<t[blue]){ lcd_print("Color = GREEN", 2000); color_ANGLE_val[green] = servo_position;}
  else if(t[blue]>t[green]){ lcd_print("Color = BLUE", 2000); color_ANGLE_val[blue] = servo_position;}
  else lcd_print("Color = white", 2000);
}

void pickObject(){
  for(int i=top_servo_pos; i<=160; i+=4){ 
    rotate_servo(top_servo, i, 500, 100);
    if( analogRead(Proximity) <= 100){ digitalWrite(electroMagnet, HIGH); delay(2000); rotate_servo(top_servo, top_servo_pos, 2000, 500); break;}
  }
}

void serialEvent(String type) {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); // add it to the taskString:
    if(type == "calib") calibrationString += inChar;
    else if(type == "task")taskString += inChar;
    if (inChar == '\n') stringComplete = true;
    Serial.println(calibrationString);
  }
}

// miscellaneous functions...........
void lcd_print(String str, int delay_time){ lcd.clear(); lcd.setCursor(0,0); lcd.print(str); delay(delay_time);}
void lcd_multiline_print(String str1, String str2, int delay_time){ lcd.clear(); lcd.setCursor(0,0); lcd.print(str1); lcd.setCursor(0,1); lcd.print(str2); delay(delay_time);}
void rotate_servo(int pin, int angle, int delay1, int delay2){ myservo.attach(pin); myservo.write(angle); delay(delay1); myservo.detach(); delay(delay2); }
