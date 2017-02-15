int flag;
int n;

void setup()
{
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  n= flag%8;
  
  if (n == 1 || n == 3 || n == 5 || n == 7)
    digitalWrite(13, HIGH);
  if (n == 2 ||n ==3 || n == 6 ||n ==7)
    digitalWrite(12,HIGH);
  if (n == 4 || n == 5 || n == 6 ||n == 7)
    digitalWrite(11, HIGH);
  delay(1000);
  flag = flag +1;
}
