#include <dhtnew.h>

DHTNEW mySensor(14);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  // READ DATA
  int chk = mySensor.read();

  // DISPLAY DATA
  Serial.print(mySensor.getHumidity(), 1);
  Serial.print(",\t");
  Serial.print(mySensor.getTemperature(), 1);
  Serial.println(",\t");
  delay(500);
}