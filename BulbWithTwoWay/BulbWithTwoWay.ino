int status=0,currentStatus=0,prevStatus=0,reading=0;
void setup() {
pinMode(13,OUTPUT);
  Serial.begin(9600);

}
void loop() {
// Serial.print("VAL:");
 if (Serial.available()) 
  {status = Serial.read()-'0';
  }
    if(status==1)digitalWrite(13,HIGH);
    if(status==0)digitalWrite(13,LOW);
reading=analogRead(3);
if(reading>800)
  {
   currentStatus=1;
  }
  else
  {
       currentStatus=0;
  }
if(currentStatus!=prevStatus)
{
  if(reading>800)
  {
    Serial.println("Turned ON");
  }
  else 
  {
    Serial.println("Turned OFF");
  }
  prevStatus=currentStatus;
}
}
