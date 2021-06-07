#include<Wire.h>
#include<DS3231.h>
RTClib realTimeClock;
DS3231 clock;
void setup() {
  // put your setup code here, to run once:
  delay(5000);
  Wire.begin();
  Serial.begin(9600);
  clock.setClockMode(false);
  clock.setYear((byte)21);
  clock.setMonth(byte(6));
  clock.setDate((byte)(8));
  clock.setHour((byte)(0));
  clock.setMinute((byte)(49));
  clock.setSecond((byte)(58));

}

void loop() {
  // put your main code here, to run repeatedly:
  
  DateTime today=realTimeClock.now();
  Serial.println(today.day());
    Serial.println(today.month());

  Serial.println(today.year());
    Serial.println(today.hour());
  Serial.println(today.minute());
    Serial.println(today.second());
    delay(2000);




}
