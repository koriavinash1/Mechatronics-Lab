#include <Servo.h> 
 
Servo myservo;  
                
 
int pos = 0;
int IRsen= 5;
 
void setup() 
{ 
  myservo.attach(6); 
  pinMode (IRsen, INPUT);
  
} 
 
 
void loop() 
{ 

  for(pos = 0; pos < 180; pos += 1)  
  {     
    if (digitalRead(IRsen)==HIGH)
       break;
    myservo.write(pos);              
    delay(15);                      
  } 
  for(pos = 180; pos>=1; pos-=1)     
  { 
    if (digitalRead(IRsen)==HIGH)
       break;    
    myservo.write(pos);              
    delay(15);                       
  } 
} 
