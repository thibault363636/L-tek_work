//#include "Adafruit_Si7021.h"

//Adafruit_Si7021 sensor = Adafruit_Si7021();



static const uint64_t UPDATE_INTERVAL = 10000;
 
unsigned long SLEEP_TIME = 56000; // Sleep time between reads (in milliseconds)

float lastTemp;
float lastHum;
uint8_t nNoUpdatesTemp;
uint8_t nNoUpdatesHum;
bool metric = true;
static const uint8_t FORCE_UPDATE_N_READS = 10;

//MyMessage msgHum(CHILD_ID_HUM, V_HUM);
//MyMessage msgTemp(CHILD_ID_TEMP, V_TEMP);

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
 
#if 0
void setup()  
{ 
  if (!sensor.begin()) {
    Serial.println("Did not find Si7021 sensor!");
    while (true);
  }
  
  // needed for battery soc
  // use the 1.1 V internal reference

}
 
void loop()     
{
  // disable ADC
  
  // get the battery Voltage
 

  delay(500);
    //Read data and store it to variables hum and temp
    hum = sensor.readHumidity();
    temp= sensor.readTemperature();
    #ifdef MY_DEBUG
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    #endif
  if (isnan(temp)) {
    Serial.println("Failed reading temperature from DHT!");
  } else if (temp != lastTemp || nNoUpdatesTemp == FORCE_UPDATE_N_READS) {
    // Only send temperature if it changed since the last measurement or if we didn't send an update for n times
    lastTemp = temp;

    #ifdef MY_DEBUG
    Serial.print("T: ");
    Serial.println(temp);
    #endif
  } else {
    // Increase no update counter if the temperature stayed the same
    nNoUpdatesTemp++;
  }

  // Get humidity from DHT library
  
  if (isnan(hum)) {
    Serial.println("Failed reading humidity from DHT");
  } else if (hum != lastHum || nNoUpdatesHum == FORCE_UPDATE_N_READS) {
    // Only send humidity if it changed since the last measurement or if we didn't send an update for n times
    lastHum = hum;
    // Reset no updates counter
    nNoUpdatesHum = 0;
//    send(msgHum.set(hum, 1));

    #ifdef MY_DEBUG
    Serial.print("H: ");
    Serial.println(hum);
    #endif
  } else {
    // Increase no update counter if the humidity stayed the same
    nNoUpdatesHum++;
  }
  
  delay(2000);  
}