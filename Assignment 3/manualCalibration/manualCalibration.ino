#include <Servo.h> 
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,8,12,13);
Servo myservo;
int whitepatch_pos = 130;
int LDR_whitepatch = 0;
int red = 9, green = 10, blue = 11;
int LDR = A2;
int val_intensity[] = {0,0,0,0,0,0,0,0,0,0,0,0};//0:red, 1:green, 2:blue
int val_current[] = {0,0,0,0,0,0,0,0,0,0,0,0};//0:red, 1:green, 2:blue // PWM values...
int Cstop = 8;
int servo_position = whitepatch_pos;

void setup(){
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(Cstop, INPUT_PULLUP);
  
  myservo.attach(6);
  myservo.write(whitepatch_pos);
  
  lcd.begin(16, 2);
  
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);
  LDR_whitepatch = analogRead(A2);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);
  
}

void loop(){
//  if(digitalRead(Cstop) == LOW){
//    Serial.print("AAAA");
//    exit(0);
//  }
//  ManualCalibrate(red);
//  delay(100);
//  digitalWrite(red, LOW);
//  ManualCalibrate(green);
//  delay(100);
//  digitalWrite(green, LOW);
//  ManualCalibrate(blue);
//  delay(100);
//   digitalWrite(blue, LOW);

  servomotion();
  AutoCalibrate(red);
  delay(100);
  digitalWrite(red, LOW);
  servomotion();
  AutoCalibrate(green);
  delay(100);
  digitalWrite(green, LOW);
  servomotion();
  AutoCalibrate(blue);
  delay(100);
  digitalWrite(blue, LOW);
  
  
  calibrateToMax(find_max(), red);
  delay(100);
  digitalWrite(red, LOW);
  calibrateToMax(find_max(), green);
  delay(100);
  digitalWrite(green, LOW);
  calibrateToMax(find_max(), blue);
  delay(100);
  digitalWrite(blue, LOW);
  
  
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
  delay(250);
  val_intensity[temp] = analogRead(LDR);
  val_current[temp] = 100;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("R:"+String(val_intensity[red])+"G:"+String(val_intensity[green])+"B:"+String(val_intensity[blue]));
  delay(1000); 
}

int find_max(){
  if((val_intensity[red] > val_intensity[green]) && (val_intensity[red] > val_intensity[blue])) return val_intensity[red];
  else if((val_intensity[blue] > val_intensity[green])) return val_intensity[blue];
  else return val_intensity[green];
}

void calibrateToMax(int max_val, int temp){
  int temp_thresh = 10;
  for(int i = 255; val_intensity[temp] <= (max_val - temp_thresh); i--){
    analogWrite(temp, i);
    delay(50);
    val_intensity[temp] = analogRead(LDR);
    delay(50);
    val_current[temp] = i;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("R:"+String(val_intensity[red])+"G:"+String(val_intensity[green])+"B:"+String(val_intensity[blue]));
    lcd.setCursor(0,1);
    lcd.print("RC:"+String(val_current[red])+"GC:"+String(val_current[green])+"BC:"+String(val_current[blue]));
    delay(500);
  }    
}

void servomotion(){
 for(int i = servo_position; i >=0; i--){
     if(analogRead(LDR)>LDR_whitepatch){
       servo_position = i;
       exit(0);
     }
 }
}
