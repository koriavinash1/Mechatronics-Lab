#include <Servo.h> 
 
Servo myservo;  
 
int potpin = A2;  
int val;
int servo = 8;
 
void setup() 
{ 
  myservo.attach(servo);  
} 
 
void loop() 
{ 
  val = analogRead(potpin);            
  val = map(val, 0, 1023, 0, 179);     
  myservo.write(val);                  
  delay(15);                           
} 
