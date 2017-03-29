#include <Servo.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,8,12,13);
Servo myservo;
int whitepatch_pos = 170;
int LDR_whitepatch = 0;
int red = 11, green = 10, blue = 9;
int LDR = A2;
int val_intensity[] = {0,0,0,0,0,0,0,0,0,0,0,0};//0:red, 1:green, 2:blue
int val_current[] = {0,0,0,0,0,0,0,0,0,0,0,0};//0:red, 1:green, 2:blue // PWM values...
int Cstop = 8;
int servo_position = whitepatch_pos;
int base_servo = 6, top_servo = 5;

void setup(){
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(Cstop, INPUT_PULLUP);
  
  myservo.attach(base_servo);
  myservo.write(whitepatch_pos);
  delay(3000);
  myservo.detach();
  delay(500);
  
  
  lcd.begin(16, 2);
  
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);
  delay(1000);
  LDR_whitepatch = analogRead(A2);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WPatch_LDR:"+String(LDR_whitepatch));
  delay(1000);
  
}

void loop(){
//  if(digitalRead(Cstop) == LOW){
//    Serial.print("AAAA");
//    exit(0);
//  }

// Manual Calibrate......
//  ManualCalibrate(red);
//  delay(100);
//  digitalWrite(red, LOW);
//  ManualCalibrate(green);
//  delay(100);
//  digitalWrite(green, LOW);
//  ManualCalibrate(blue);
//  delay(100);
//   digitalWrite(blue, LOW);

//Auto Calibrate...............
  AutoCalibrate(red);
  digitalWrite(red, LOW);
  
  AutoCalibrate(green);
  digitalWrite(green, LOW);

  AutoCalibrate(blue);
  digitalWrite(blue, LOW);
 
 
// Calibrate to max............. 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("calib to max.....");
  delay(2000);
  
  int maxValue = find_max();
  
  calibrateToMax(maxValue, red);
  digitalWrite(red, LOW);
  
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Done RED....");
//  delay(2000); 

  calibrateToMax(maxValue, blue);
  digitalWrite(blue, LOW);
 
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Done BLUE....");
//  delay(2000); 
  
  calibrateToMax(maxValue, green);
  digitalWrite(green, LOW);
  
// calibration done......
  delay(5000);
  
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("Done GREEN....");
//  delay(2000); 
 
// find color....  

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("finding color.....");
  delay(2000);
  int color = 0;

  myservo.attach(6);
  servomotion();
  myservo.detach();
  color = find_color();
  delay(100);
  
  lcd.clear();
  lcd.setCursor(0,0);
  if(color == 11) lcd.print("Color = RED");
  else if(color == 10) lcd.print("Color = GREEN");
  else if(color == 9) lcd.print("Color = BLUE");
  else lcd.print("Color = junk");
  delay(2000); 
  
  
  myservo.attach(6);
  servomotion();
  myservo.detach();
  color = find_color();
  delay(100);
  
  lcd.clear();
  lcd.setCursor(0,0);
  if(color == 11) lcd.print("Color = RED");
  else if(color == 10) lcd.print("Color = GREEN");
  else if(color == 9) lcd.print("Color = BLUE");
  else lcd.print("Color = junk");
  delay(2000);
  
  
  myservo.attach(6);
  servomotion();
  myservo.detach();
  color = find_color();
  delay(100);
  
  lcd.clear();
  lcd.setCursor(0,0);
  if(color == 11) lcd.print("Color = RED");
  else if(color == 10) lcd.print("Color = GREEN");
  else if(color == 9) lcd.print("Color = BLUE");
  else lcd.print("Color = junk");
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Done..."); 
  
  exit(0);
}

void ManualCalibrate(int temp){    
  digitalWrite(temp, HIGH);
  delay(50);
  val_intensity[temp] = analogRead(LDR);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("R:"+String(val_intensity[red])+"G:"+String(val_intensity[green])+"B:"+String(val_intensity[blue]));
  delay(500);
}

void AutoCalibrate(int temp){
  analogWrite(temp, 255);   
  delay(200);
  val_intensity[temp] = analogRead(LDR);
  val_current[temp] = 255;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("R:"+String(val_intensity[red])+"G:"+String(val_intensity[green])+"B:"+String(val_intensity[blue]));
  delay(500); 
}

int find_max(){
  if((val_intensity[red] > val_intensity[green]) && (val_intensity[red] > val_intensity[blue])) return val_intensity[red];
  else if((val_intensity[blue] > val_intensity[green])) return val_intensity[blue];
  else return val_intensity[green];
}

void calibrateToMax(int max_val, int temp){
  int temp_thresh = 10;
  
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("temp..."+ String(temp));
//  delay(2000); 
//  
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("max_val."+ String(max_val));
//  delay(2000);
  
  for(int i = 255; val_intensity[temp] <= (max_val - temp_thresh); i--){
    analogWrite(temp, i);
    delay(100);
    val_intensity[temp] = analogRead(LDR);
    val_current[temp] = i;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("R:"+String(val_intensity[red])+"G:"+String(val_intensity[green])+"B:"+String(val_intensity[blue]));
    lcd.setCursor(0,1);
    lcd.print("RC:"+String(val_current[red])+"GC:"+String(val_current[green])+"BC:"+String(val_current[blue]));
    delay(1000);
  }    
}

void servomotion(){
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);
  for(int i = servo_position; i >=0; i--){
    myservo.write(i);
    delay(50);
     if((analogRead(LDR) <= (LDR_whitepatch-5)) && (i < (servo_position - 8))){
       servo_position = i;
       break;
     }
  }
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
}

int find_color(){
  int temp_thresh = 10;

  analogWrite(red, val_current[red]);
  delay(500);
  if(analogRead(LDR) <= (val_intensity[red]-temp_thresh)) return red;
  digitalWrite(red, LOW);
  
  analogWrite(green, val_current[green]);
  delay(500);
  if(analogRead(LDR) <= (val_intensity[green]-temp_thresh)) return green;
  digitalWrite(green, LOW);
  
  analogWrite(blue, val_current[blue]);
  delay(500);
  if(analogRead(LDR) <= (val_intensity[blue]-temp_thresh)) return blue;
  digitalWrite(blue, LOW);
}
