#include "myServer.h"
#include "serverHTML.h"
#include "myDHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ESP8266_Weather"; // Replace for station mode
const char* password = "12345678"; // Replace for station mode

ESP8266WebServer server(80);
IPAddress lastConnectedIPs[5];

void handleRoot() {
  String html = FPSTR(HTML_HEAD);
  html += FPSTR(HTML_SCRIPT);
  server.send(200, "text/html", html);
}

void handleData() {
  String json = "{";
  json += "\"humidity\":" + String(humidity, 2) + ",";
  json += "\"temperatureC\":" + String(temperature, 2) + ",";
  json += "\"temperatureF\":" + String(temperatureF, 2);
  json += "}";
  server.send(200, "application/json", json);
}

void checkNewConnections() {
  struct station_info *stat_info = wifi_softap_get_station_info();
  int i = 0;

  while (stat_info != NULL) {
    IPAddress ip = IPAddress(stat_info->ip.addr);
    bool isNew = true;

    for (int j = 0; j < 5; j++) {
      if (ip == lastConnectedIPs[j]) {
        isNew = false;
        break;
      }
    }

    if (isNew) {
      Serial.println("New device connected:");
      Serial.print("IP Address: ");
      Serial.println(ip);
      Serial.print("MAC Address: ");
      for (int k = 0; k < 6; k++) {
        Serial.print(stat_info->bssid[k], HEX);
        if (k < 5) Serial.print(":");
      }
      Serial.println();

      lastConnectedIPs[i % 5] = ip;
      i++;
    }

    stat_info = STAILQ_NEXT(stat_info, next);
  }

  wifi_softap_free_station_info();
}

void initServer() {
  WiFi.softAP(ssid, password);
  Serial.println();
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");
  Serial.print("Use password \"");
  Serial.print(password);
  Serial.println("\" to connect with it."); 
  Serial.println("Visit http://192.168.4.1 in a browser to view data.");

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
  Serial.println("HTTP server started");
}

void updateServer() {
  server.handleClient();
  checkNewConnections();
}
