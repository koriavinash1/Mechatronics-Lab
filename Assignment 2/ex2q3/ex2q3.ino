#include <Servo.h>

Servo myservo;  

int pos = 0;
int isObstaclePin = 7;  
int isObstacle = HIGH;    
void setup() {
  myservo.attach(9); 
 pinMode(isObstaclePin, INPUT); 
 Serial.begin(9600);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { 
    myservo.write(pos);             
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);
  }
 isObstacle = digitalRead(isObstaclePin);
  if (isObstacle == LOW)
  
}
