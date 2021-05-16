int x;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12,OUTPUT);
}

void loop() {
  if(Serial.available())
  {
    x=Serial.read();
    Serial.println(x);
    if(x=='1')digitalWrite(12,HIGH);
    if(x=='0')digitalWrite(12,LOW);
    }
  // put your main code here, to run repeatedly:

}
