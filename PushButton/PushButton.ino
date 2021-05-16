void setup() {
 pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
    pinMode(8,OUTPUT);


 Serial.begin(9600);
}
int x,y;
void loop() {
  Serial.println(x);

  // put your main code here, to run repeatedly:
x=digitalRead(5);
if(x==1)
{
  delay(300);
}
y=digitalRead(5);
if(x==1&&y==1)
{
    Serial.println("if");
    digitalWrite(8,LOW);

 digitalWrite(6,HIGH);
 
      
}
else if(x==1&&y==0)
{
  Serial.println("Else if");
    digitalWrite(8,HIGH);
        digitalWrite(6,LOW);

}
else
{
  digitalWrite(6,LOW);
   digitalWrite(8,LOW); 
}if(x==1)
{
  delay(500);
}
}
