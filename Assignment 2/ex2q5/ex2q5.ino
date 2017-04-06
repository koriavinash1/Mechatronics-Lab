/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */
 #include <Servo.h>
 Servo myservo;
 int pos = 0;
 int p=0;
 
 

String inputString = "1";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  myservo.attach(6);
  inputString.reserve(200);
}

void loop() {
  
  // print the string when a newline arrives:
  serialEvent();
  //Serial.println(stringComplete);
  if (stringComplete) {
    Serial.println(inputString);
    if(inputString=="1")
    {
      prev=inputString;
      for(pos=p;pos<180;pos++)
     {myservo.write(pos);
     p=pos;
          }
      for(pos=p;pos>0;pos--)
      {myservo.write(pos);
      p=pos;
     
      }
      delay(500);
    }
    else if(inputString=="0")
  {prev=inputString;}
    else 
    inputString=prev;
    
    // clear the string:
   // inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    //Serial.println("a");
   // Serial.println("inSE");
     char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}


