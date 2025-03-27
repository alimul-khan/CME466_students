#include <Arduino.h>
#include "myDHT.h"
#include "myServer.h"

void setup() {
  delay(200);
  Serial.begin(115200);
  delay(1000);
  initDHT();
  initServer();
  
}

void loop() {
  getTempHumidity();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C / ");
  Serial.print(temperatureF);
  Serial.println("°F");

  updateServer();

  delay(1000);
}
