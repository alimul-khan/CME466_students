void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED pin as an output
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW); // Turn LED ON (LOW is ON for ESP8266)
  delay(200); // Wait 1 second
  digitalWrite(LED_BUILTIN, HIGH); // Turn LED OFF
  delay(200); // Wait 1 second
}
