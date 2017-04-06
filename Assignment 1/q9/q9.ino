
int value;
int potpin = A2;

void setup()
{
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  value = analogRead(potpin);
  value = map(value, 0, 1023, 0, 255);
  analogWrite(6, value);
  Serial.println(value);
}

