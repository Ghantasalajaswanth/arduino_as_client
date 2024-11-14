This project demonstrates how to use an Arduino with a DHT11 sensor to monitor real-time temperature and humidity data. The Arduino is equipped with an Ethernet shield, which enables it to act as a web server. The setup allows data from the DHT sensor to be accessed both through the Serial Monitor and via a web page on a specified IP address.

Project Overview
Hardware: Arduino with DHT11/DHT22 sensor and Ethernet shield.
Objective: To retrieve temperature and humidity data and make it accessible over the network as well as in the Serial Monitor.
Connection Setup:
The DHT sensor is connected to the Arduino (data pin set to a digital pin).
The Ethernet shield is connected to the Arduino and directly linked to a PC via an Ethernet cable.
IP Address Assignment: The Arduino is assigned a static IP address to serve the web page.
Data Access: DHT data can be accessed in real-time via:
Serial Monitor: For monitoring sensor values directly.
Web Server: For accessing sensor data through a web browser on the PC.
Circuit Connections
DHT Sensor:

VCC → 5V on Arduino
GND → GND on Arduino
DATA → Digital pin (e.g., D2) on Arduino
Ethernet Shield:

Directly connected to the PC via an Ethernet cable.
Assigned a static IP address.
Usage
Upload the code to the Arduino, ensuring that the IP address is correctly set in the sketch.
Open the Serial Monitor to verify DHT sensor readings.
On your PC, open a web browser and enter the Arduino’s IP address to view the sensor data on the web page.
