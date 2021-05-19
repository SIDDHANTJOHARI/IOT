void setup()
{
  Serial.begin(9600);
  pinMode(3,INPUT);
  pinMode(6,OUTPUT);
}
int x;
void loop()
{
  x=digitalRead(3);
 
  if(x==1)digitalWrite(6,HIGH);
  else digitalWrite(6,LOW);
  delay(500);
  
}
