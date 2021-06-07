#include<SoftwareSerial.h>
  SoftwareSerial wifi(4,5);
int x,i,j,k=0;
char c;
char responseBuffer[101];
char deviceName[21];

void setup() {
Serial.begin(9600);
//9 FAN
pinMode(9,OUTPUT);
//10 AC
pinMode(10,OUTPUT);
//11 Cooler
pinMode(11,OUTPUT);
Serial.println("Setting up Wifi");
wifi.begin(9600);
while(!wifi); //good Practive
wifi.print("AT+RST\r\n");
delay(1000);
while(wifi.available())Serial.print((char)wifi.read());
wifi.print("AT\r\n");
delay(1000);
while(wifi.available())Serial.print((char)wifi.read());
wifi.print("AT+CWMODE=1\r\n");
delay(20000);
while(wifi.available())Serial.print((char)wifi.read());
wifi.print("AT+CWQAP\r\n");
delay(2000);
while(wifi.available())Serial.print((char)wifi.read());
wifi.print("AT+CWJAP_CUR=\"siddhantjohari\",\"bellaciaom\"\r\n");
x=1;
while(x<=5)
{
  delay(2000);
  while(wifi.available())Serial.print((char)wifi.read());
x++;
}
Serial.println("Connected to HOTSPOT");
Serial.println("Connecting to Server");
wifi.print("AT+CIPSTART=\"TCP\",\"192.168.43.8\",7892\r\n");
delay(5000);
while(wifi.available())Serial.print((char)wifi.read());
Serial.println("Connected to IOT Server");
Serial.println("Registering on Server");
wifi.print("AT+CIPSEND=24\r\n");
delay(2000);
while(wifi.available())Serial.print((char)wifi.read());
wifi.print("BR,Cherry,FAN,AC,COOLER#");
delay(3000);
while(wifi.available())Serial.print((char)wifi.read());
Serial.println("Registered on Server");
}

void loop() {
delay(5000);
Serial.println("Connecting to Server");
wifi.print("AT+CIPSTART=\"TCP\",\"192.168.43.8\",7892\r\n");
delay(5000);

while(wifi.available())Serial.print((char)wifi.read());
  // put your main code here, to run repeatedly:
Serial.println("Connected to IOT Server");
Serial.println("Sending Command Request");
wifi.print("AT+CIPSEND=10\r\n");
delay(2000);
while(wifi.available())Serial.print((char)wifi.read());
wifi.print("BC,Cherry#");
delay(3000);
if(!wifi.find((char *)"+IPD,"))
{
  i=0;
  for(i=0;wifi.available()&&i<199;i++,wifi.read());
Serial.println("SOME PROBLEM");
}
else
{
  wifi.find((char *)":");
x=0;
while(true)
{
  c=(char)wifi.read();
 if(c=='#')break;
  
  responseBuffer[x]=c;
x++;
}
responseBuffer[x]='\0';
Serial.println("Command to Execute");
if(x==0)
{
Serial.println("NO commands to execute");
}
else
{
  for(i=0;i<x;i=j+1)
  {
    k=0;
    for(j=i;j<x&&responseBuffer[j]!=',';j++,k++)
    {
      deviceName[k]=responseBuffer[j];  
    }
    deviceName[k]='\0';
    j++;
    if(strcmp(deviceName,"FAN")==0)
    {
      Serial.print("FAN:");
      Serial.println(responseBuffer[j]);
      digitalWrite(9,responseBuffer[j]-48);
    }
    else if(strcmp(deviceName,"COOLER")==0)
    { 
      Serial.print("COOLER:");
      Serial.println(responseBuffer[j]);
      digitalWrite(10,responseBuffer[j]-48);
    }
    else if(strcmp(deviceName,"AC")==0)
    {
      Serial.print("AC:");
      Serial.println(responseBuffer[j]);
     digitalWrite(11,responseBuffer[j]-48);

    }
    j++;
  }
  
}
}
}
