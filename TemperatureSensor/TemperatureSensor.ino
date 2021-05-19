#include<DHT.h>
DHT dht(3,DHT11);
void setup() {
  // put your setup code here, to run once:
delay(5000);
Serial.begin(9600);
dht.begin();
}

void loop() {
  delay(3000);
 float humidity= dht.readHumidity();
 float temperatureC=dht.readTemperature();
 float temperatureF=dht.readTemperature(true);
 float heatIndex=dht.computeHeatIndex(temperatureF,humidity);
 Serial.print("Humidity:");
 Serial.println(humidity);
  Serial.print("Temperature (C):");
 Serial.println(temperatureC);
  Serial.print("Temperature (F):");
 Serial.println(temperatureF);
 Serial.println("Heat Index (F)");
 Serial.println(heatIndex);
  // put your main code here, to run repeatedly:

}
