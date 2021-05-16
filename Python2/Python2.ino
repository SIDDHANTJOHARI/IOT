int index;
int input;
char command[51];
void setup() {
  pinMode(6,OUTPUT);
  pinMode(11,OUTPUT);
  // put your setup code here, to run once:
Serial.begin(9600);
index=0;
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available())
{
  input=Serial.read();
  if(input=='\n')
  {
    command[index]='\0';
    index=0;
    if(strcmp(command,"turn on ac")==0)digitalWrite(6,HIGH);
    else if(strcmp(command,"turn off ac")==0)digitalWrite(6,LOW);
    else if(strcmp(command,"turn on fan")==0)digitalWrite(11,HIGH);
    else if(strcmp(command,"turn off fan")==0)digitalWrite(11,LOW);
    Serial.print("Command received :");
    Serial.println(command);
    return;
  }
  
  if(input!='\r'&&input!='\n')command[index++]=(char)input;
}
}
