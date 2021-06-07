int x,y;
int buttonOld[8]={0,0,0,0,0,0,0,0};
int buttonNew[8]={0,0,0,0,0,0,0,0};

void setup() {
Serial.begin(9600);
for(x=3;x<=10;x++)pinMode(x,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:  
  for(x=3;x<=10;x++)
  {
    y=digitalRead(x);
    buttonNew[x-3]=y;
    if(buttonNew[x-3]==1&&buttonOld[x-3]==0)
    {
      Serial.print("Number:");
      Serial.print(x-2);
      Serial.println("Pressed");
      tone(12,1000);
      delay(50);
      noTone(12);
    }
    buttonOld[x-3]=y;
  }

}
