
#include<SoftwareSerial.h>
#define DEBUG true 
#define FAST 1000
#define MEDIUM 2000
#define SLOW 3000
/*
 * D4 represents FAN
 * D5 represents Porch Light
 * D6 represents AC
 */
typedef struct _model
{
char d2;
char d3;
char d4;
char d5;
char d6;
char d7;
char d8;
char d9;
char d10;
char d11;
char d12;
char key[5];
}Model;
void tmLoadModel();
void tmInitPins();
void tmInitComponents();
void tmResetWiFi();
void tmATTest();
void tmSetMode();
void tmStartServer();
void tmDumpWiFiData();
void tmProcessRequest();
int input,cid,pinToOperate;
char requestBuffer[101];
char command;
char responseBuffer[101];
void debug(char a){if(DEBUG)Serial.println(a);}
void debug(const char *a){if(DEBUG)Serial.println(a);}
void debug(int a){if(DEBUG)Serial.println(a);}


void blinkIt(byte pin,int duration,byte times)
{
while(times>=1)
{
 digitalWrite(pin,HIGH);
 delay(duration);
  digitalWrite(pin,LOW);
 delay(duration);
times--;

}
}


Model model; //global structure representing the state of various variables.
SoftwareSerial wifi(8,9); //RX of ESP and TX of ESP
/* 
 *  wifi.print(data)---->to send data to ESP
 *  wifi.read()--->to read data from ESP
 *  
 */
void setup() {

 pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
 wifi.begin(9600);
   Serial.println("Setting Up");
 tmLoadModel();
 tmInitPins();
 tmInitComponents();

 delay(2000);
 while(!wifi);
tmATTest();
blinkIt(LED_BUILTIN,FAST,4);
tmSetMode();
blinkIt(LED_BUILTIN,FAST,4);
tmStartServer();
blinkIt(LED_BUILTIN,MEDIUM,5);
digitalWrite(LED_BUILTIN,HIGH);

}

void loop() {
  if(wifi.available())
  {
    tmProcessRequest();
  }

}
void tmLoadModel(){
  model.d2='N';
  model.d3='N';
  model.d4='Y';
  model.d5='Y';
  model.d6='Y';
  model.d7='N';
  model.d8='N';
  model.d9='N';
  model.d10='N';
  model.d11='N';
  model.d12='N';
  strcpy(model.key,"1234");
 
}
void tmInitPins()
{
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}
void tmInitComponents()
{
  model.d4='0';
   model.d5='0';
    model.d6='0';
}
void tmResetWiFi()
{
  wifi.print("AT+RST\r\n");
  delay(1000);
  tmDumpWiFiData();
  }
void tmATTest(){

  wifi.print("AT\r\n");
  delay(1000);
  tmDumpWiFiData();
}
void tmSetMode(){
  
   wifi.print("AT+CWMODE=2\r\n");
  delay(1000);
  tmDumpWiFiData();
}
void tmStartServer(){
   wifi.print("AT+CIPMUX=1\r\n");
  delay(1000);
  tmDumpWiFiData();
   wifi.print("AT+CIPSERVER=1,80\r\n");
  delay(1000);
  tmDumpWiFiData();
}
int dumpInput;
void tmDumpWiFiData(){
   sprintf(responseBuffer,"");
  while(1)
  {
  dumpInput=wifi.read();
  if(dumpInput==-1)break;
  sprintf(responseBuffer,"%s%c",responseBuffer,(char)dumpInput);
  
  }
  debug(responseBuffer);
}

void tmProcessRequest(){
  delay(100);
  if(!wifi.find((char *)"+IPD,"))
  {
 tmDumpWiFiData();
    return;
  }
  delay(100);
  input=wifi.read();
  cid=input-48;
  delay(100);
  sprintf(requestBuffer,":GET /%s",model.key);
  if(!wifi.find(requestBuffer))
  {
    sprintf(requestBuffer,"AT+CIPSEND=%d,59\r\n",cid);
    wifi.print(requestBuffer);
    delay(1000);
    wifi.find((char *)">");
    wifi.print("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 0\n\n");
    delay(200);
    sprintf(requestBuffer,"AT+CIPCLOSE=%d\r\n",cid);
    wifi.print(requestBuffer);
   tmDumpWiFiData();
    debug("Blank Page Send Because Reuest is Incorrect");
    return;
  }
  input=wifi.read();
  if(input='/')
  {
    pinToOperate=wifi.read()-48;
    input=wifi.read();
    if(input!='/')
    {
      pinToOperate=pinToOperate*10+input-48;
      input=wifi.read(); //to Read front slash after second digit of pin number
    }
    command=(char)wifi.read();
   
      if(command=='1')digitalWrite(pinToOperate,HIGH);
      if(command=='0')digitalWrite(pinToOperate,LOW);
      if(pinToOperate==4)
   {
    model.d4=command;
   }
   if(pinToOperate==5)
   {
    model.d5=command;
   }
      
  }
   sprintf(requestBuffer,"AT+CIPSEND=%d,461\r\n",cid);
    wifi.print(requestBuffer);
    delay(1000);
    wifi.find((char *)">");
    wifi.print("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 388\n\n<!DOCTYPE html><html><head><meta charset='utf-8'><title>Siddhant Home Network</title></head><body style='font-size: 24pt'><center><b>Siddhant Home Network</b>><br/>Porch Light <a href='/1234/4/");
    if(model.d4=='0')
    {
    wifi.print("1'>Turn on Porch light</a> <br/>Lamp <a href='/1234/5/");
    }  
    if(model.d4=='1')
    {
        wifi.print("0'>Turn off Porch light</a><br/>Lamp <a href='/1234/5/");
    }
    if(model.d5=='0')
    {
    wifi.print("1'>Turn on Lamp</a> <br/><br/><br/><a href='/1234/CK'>Change Key</a><br/><a href='/1234/CA'>Change Access Point Details</a></center></body></html>");
    }
    if(model.d5=='1')
    {
    wifi.print("0'>Turn off Lamp</a><br/><br/><br/><a href='/1234/CK'>Change Key</a><br/><a href='/1234/CA'>Change Access Point Details</a></center></body></html>");
    }
    delay(200);
    sprintf(requestBuffer,"AT+CIPCLOSE=%d\r\n",cid);
    wifi.print(requestBuffer);
   tmDumpWiFiData();
    debug("Default Page Sent");
    
  //as of now just send default page
  
  
  //do nothing right now
}
