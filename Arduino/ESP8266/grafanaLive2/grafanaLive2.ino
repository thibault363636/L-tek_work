/**
  Grafana Live example
  - connects to WiFi
  - gets current time via NTP
  - starts sending data to Grafana via POST requests

  Grafana automatically creates a data source via
  Data source [-- Grafana --] > Query type [Live Measurements]

  Select the measurement channel under stream/[GRAFANA_STREAM_NAME]
*/

// WiFi to connect to
#define WIFI_NAME ""
#define WIFI_PASSWORD ""

// Grafana server to use
#define GRAFANA_SERVER "http://something.com:1234"

// The name of the stream as displayed in Grafana
#define GRAFANA_STREAM_NAME "nodemcu"

// Authorization token for Grafana
// Set up in Grafana in Home > Administration > Service accounts
//    Create an Admin account and add a service account token
#define GRAFANA_AUTH_TOKEN ""


#include <Arduino.h>

#include <ESP8266WiFi.h>        // esp8266 / Arduino              -- install via Boards manager, Additional board manager URL https://arduino.esp8266.com/stable/package_esp8266com_index.json
#include <ESP8266WiFiMulti.h>   // esp8266 / Arduino
#include <ESP8266HTTPClient.h>  // esp8266 / Arduino
#include <NTPClient.h>          // arduino-libraries / NTPClient  -- install via Library manager
#include <WiFiClient.h>         // standard
#include <WiFiUdp.h>            // standard

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;
HTTPClient http;
WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "pool.ntp.org");

int ThermistorPin = 0;
int Vo;
float r;
float a = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 0.0008802379350954048, c2 = 0.00025261779329179923, c3 = 1.8747408754669722e-07;
float b = 440.9030052843748;
float c = 2000;
float e = 881;
float d = 3.3;


void setup() {

  Serial.begin(115200);
  //Serial.setDebugOutput(true);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_NAME, WIFI_PASSWORD);
}

bool setupTime() {
  bool status = true;

  // Perform NTP update only once
  static
  bool done = false;

  if (!done) {
    if ((WiFiMulti.run() == WL_CONNECTED)) {
      status = timeClient.update();
      if (status)
        done = true;
    }
  }
  return status;
}

void loop() {

 // Mesure la tension sur la broche A0
  int valeur = analogRead(A0);

  // Transforme la mesure (nombre entier) en tension via un produit en croix
  float v = valeur * (3.3 / 1023.0);

  // Envoi la mesure au PC pour affichage et attends 250ms
  Serial.println(v);
  

 Vo = analogRead(ThermistorPin);
  r  = (e*d*a*b + e*d*a*c - d*a*b*c - e*v*a*b) / (b* (e*v + d*c));
  T = 1.0/(c1 + c2* (log(r)) + c3* (log(r)*log(r)*log(r)));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: ");
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");
  Serial.println( r );
  Serial.println( T );

  bool status = true; // true == everything OK

  status = setupTime();
  if (!status)
      Serial.println("NTP failed");

  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    if (status) {
      status = http.begin(client, String() + GRAFANA_SERVER + "/api/live/push/" + GRAFANA_STREAM_NAME);
      if (!status)
        Serial.println("HTTP failed");
    }

    if (status) {
      http.addHeader("Authorization", GRAFANA_AUTH_TOKEN);

      float data = Tc; // Store your measurement here

      String dataPoint = String() + "test data=" + data + " " + timeClient.getEpochTime() + "000000000";
      Serial.println(dataPoint);
      int httpCode = http.POST(dataPoint);

      if (httpCode < 0) {
        Serial.printf("HTTP failed, error: %s\n", http.errorToString(httpCode).c_str());
        status = false;
      }
      http.end();
    } else {
      status = false;
    }
  }

  delay(500);

 
}
