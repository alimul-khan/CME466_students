# CME466_students

This repository contains project folders developed for the CME466 course. Each folder represents a progressive step in working with ESP microcontrollers, covering topics from basic GPIO blinking to cloud-based IoT applications.

## Folder Structure

The folders are intentionally organized in the following sequence to reflect the recommended learning flow:

1. **espBlink**  
   A simple example to blink an onboard LED using the ESP module. Serves as a starting point for working with GPIO.

2. **espDHT22**  
   Demonstrates how to interface a DHT22 temperature and humidity sensor with the ESP and read sensor data.

3. **espAccessPoint**  
   Configures the ESP to work as a Wi-Fi Access Point, enabling direct device-to-device communication.

4. **espStation**  
   Connects the ESP to a predefined Wi-Fi network as a client (station mode). Note: ESP cannot connect to networks like `uofs-secure` or `uofs-public` due to authentication restrictions.

5. **espCloud**  
   Sends sensor data from the ESP to a local or cloud-based server using HTTP requests.

6. **espCloudApp**  
   Contains a Python-based server and visualization dashboard to receive and display data sent from the ESP.  

   📌 To run the application, execute:
   ```bash
   python3 espCloudApp.py


## Notes

- The ESP module **cannot connect** to `uofs-secure` or `uofs-public` Wi-Fi networks due to incompatible security protocols.
- Please ensure your ESP and computer are connected to the same local Wi-Fi network (e.g., a personal hotspot or a non-restricted access point).

## Author

Developed and maintained by **Alimul Haque Khan**,  
CME466: Embedded Systems and IoT  
Department of Electrical & Computer Engineering  
University of Saskatchewan
