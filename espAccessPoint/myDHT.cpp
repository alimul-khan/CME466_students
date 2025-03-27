#include "myDHT.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN D3 
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

float humidity = 0.0;
float temperature = 0.0;
float temperatureF = 0.0;

void initDHT() {
  dht.begin();
}

void getTempHumidity() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float tF = dht.readTemperature(true);
  delay(1000);

  if (isnan(h) || isnan(t) || isnan(tF)) {
    Serial.println("Failed to read from DHT sensor! Using default values.");
    humidity = 5.0;
    temperature = 0.0;
    temperatureF = 32.0;
    return;
  }

  humidity = h;
  temperature = t;
  temperatureF = tF;
}
