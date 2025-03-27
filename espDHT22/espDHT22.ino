#include <Adafruit_Sensor.h>
#include <DHT.h>

// Define DHT22 sensor pin
#define DHTPIN D3 
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

// Global variables to hold values
float humidity = 0.0;
float temperature = 0.0;
float temperatureF = 0.0;

// Function prototype
void getTempHumidity();


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


void setup() {
  delay(200);
  Serial.begin(115200);
  dht.begin();
  Serial.println("DHT22 sensor initialized");
}

void loop() {
  getTempHumidity();

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");

  Serial.print("Temperaturre: ");
  Serial.print(temperature);
  Serial.print("°C / ");
  Serial.print(temperatureF);
  Serial.println("°F");

  delay(2000);
}
