
// you have to run a server, in this example i used a python server

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "SensorData.h"  // Include the sensor functions

const char* ssid = "Alim5G";
const char* password = "AllimBhai";
const char* serverIP = "10.0.0.181"; // Flask Server IP, you have to find you ip using any available method.

String chipID;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");


    //    chipID = String(ESP.getChipId(), HEX); // You may replace this by your nsid
    chipID = "abc123";
    Serial.print("From server computer, use this link: http://127.0.0.1:5000/node/");
    Serial.println(chipID);

    Serial.print("From any other device on the same network, use this link: http://");
    Serial.print(serverIP);
    Serial.print("/node/");
    Serial.println(chipID);


}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        String commandURL = "http://" + String(serverIP) + ":5000/command?chip_id=" + chipID;
        http.begin(client, commandURL);
        int httpResponseCode = http.GET();

        if (httpResponseCode == 200) {
            String response = http.getString();
            Serial.print("Server Command: ");
            Serial.println(response);
            http.end();

            if (response.indexOf("get_temp") != -1) {
                sendTemperature();
            } 
            else if (response.indexOf("get_humidity") != -1) {
                sendHumidity();
            }
        } else {
            Serial.print("Failed to get command, HTTP Code: ");
            Serial.println(httpResponseCode);
            http.end();
        }
    }

    delay(500);
}

void sendTemperature() {
    WiFiClient client;
    HTTPClient http;

    float temp = generateTemperature();  // Now calling from SensorData.cpp
    Serial.print("Generated Temperature: ");
    Serial.println(temp);

    String postURL = "http://" + String(serverIP) + ":5000/send_temp?chip_id=" + chipID;
    http.begin(client, postURL);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"temperature\":" + String(temp, 2) + "}";
    int postResponse = http.POST(jsonPayload);

    Serial.print("Temperature Sent. Server Response: ");
    Serial.println(postResponse);

    http.end();
}

void sendHumidity() {
    WiFiClient client;
    HTTPClient http;

    float humidity = generateHumidity();  // Now calling from SensorData.cpp
    Serial.print("Generated Humidity: ");
    Serial.println(humidity);

    String postURL = "http://" + String(serverIP) + ":5000/send_humidity?chip_id=" + chipID;
    http.begin(client, postURL);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"humidity\":" + String(humidity, 2) + "}";
    int postResponse = http.POST(jsonPayload);

    Serial.print("Humidity Sent. Server Response: ");
    Serial.println(postResponse);

    http.end();
}
