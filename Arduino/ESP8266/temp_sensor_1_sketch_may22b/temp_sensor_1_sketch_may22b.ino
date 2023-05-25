#include <OneWire.h>
#include <DallasTemperature.h>
 
#define PIN_TEMPERATURE 14
 
OneWire oneWire(PIN_TEMPERATURE);
DallasTemperature sensors(&oneWire);
 
float currentTemp = 0;
 
 
void setup() {
 
  Serial.begin(115200);
   
}
 
void loop() {
 
  sensors.requestTemperatures();
  currentTemp = sensors.getTempCByIndex(0);
   
  Serial.print("Temperature con9: ");
  Serial.println(currentTemp);
   
  delay(500);
 
}