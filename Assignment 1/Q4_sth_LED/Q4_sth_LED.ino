int led1 = 13, led2 = 12, led3 = 11;
int sth1 = 7, sth2 = 8, sth3 = 9; //switch

void setup(){
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  pinMode(sth1, INPUT_PULLUP);
  pinMode(sth2, INPUT_PULLUP);
  pinMode(sth3, INPUT_PULLUP);
}

void loop(){
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  
  if(digitalRead(sth1) == LOW)
    digitalWrite(led1, HIGH);
  
  if(digitalRead(sth2) == LOW)
    digitalWrite(led2, HIGH);
  
  if(digitalRead(sth3) == LOW)
    digitalWrite(led3, HIGH);  
}
