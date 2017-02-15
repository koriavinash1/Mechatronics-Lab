String astr='',bstr='';

int a = 0, b = 0, c = 0;

String str = "";
boolean stringComplete = false; 

void setup(){
  Serial.begin(9600);
  str.reserve(200);
}

void loop(){
  if (stringComplete){
    for(int i = 0; i < str.length(); i++){
      if(str[i] == 'a')
        a = i;
      if(str[i] == 'b')
        b = i;
      if(str[i] == 'c')
        c = i;
    }
    for(int j = a+1; j < b; j++)
      astr += str[j];
      
    for(int k = b+1; k < c; k++)
      bstr += str[k];
  } 
  Serial.print(astr + '\t');
  Serial.println(bstr);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    str += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

