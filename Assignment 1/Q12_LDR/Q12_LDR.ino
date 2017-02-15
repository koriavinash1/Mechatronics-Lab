void setup(){
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(13, LOW);
  Serial.println(analogRead(A3));
  if(analogRead(A3)> 400)
    digitalWrite(13, HIGH);
}
