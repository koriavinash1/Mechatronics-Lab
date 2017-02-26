int led = 13;
int sth = 7; //switch

void setup(){
  pinMode(led, OUTPUT);
  pinMode(sth, INPUT_PULLUP);
}

void loop(){
  digitalWrite(led, LOW);
  if(digitalRead(sth) == LOW)
    digitalWrite(led, HIGH);  
}
