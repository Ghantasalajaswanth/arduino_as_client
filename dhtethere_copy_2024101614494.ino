#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

#define DHTPIN 2          // Pin where the DHT sensor is connected
#define DHTTYPE DHT11     // DHT11 or DHT22

DHT dht(DHTPIN, DHTTYPE);

// MAC address for Ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetServer server(80);  // Initialize the Ethernet server at port 80 (HTTP)

void setup() {
  // Start the Serial communication
  Serial.begin(9600);

  // Start Ethernet with DHCP:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // If DHCP fails, use a static IP (fallback)
    IPAddress fallbackIP(172, 16, 57, 72); // Replace with your fallback IP
    Ethernet.begin(mac, fallbackIP);
  }

  // Start the DHT sensor
  dht.begin();

  // Start the server
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());  // Display the assigned IP address
}

void loop() {
  // Wait for a client to connect
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Client connected");
    
    // Wait until the client sends data
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        // If the client sent a newline, it indicates the end of the request
        if (c == '\n' && currentLineIsBlank) {
          // Read temperature and humidity from DHT sensor
          float h = dht.readHumidity();
          float t = dht.readTemperature();
          
          // Check if reading failed and print error message
          if (isnan(h) || isnan(t)) {
            Serial.println("Failed to read from DHT sensor!");
          } else {
            // Print the values to the Serial Monitor
            Serial.print("Temperature: ");
            Serial.print(t);
            Serial.println(" °C");
            Serial.print("Humidity: ");
            Serial.print(h);
            Serial.println(" %");
          }

          // HTTP response headers
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();

          // HTML content
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<h1>Temperature and Humidity Monitor</h1>");
          if (isnan(h) || isnan(t)) {
            client.println("<p>Failed to read from DHT sensor!</p>");
          } else {
            client.println("<p>Temperature: " + String(t, 2) + " °C</p>");  // Format with 2 decimal places
            client.println("<p>Humidity: " + String(h, 2) + " %</p>");      // Format with 2 decimal places
          }
          client.println("</html>");

          break;
        }

        // Handle newlines received from the client
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    // Give the client time to receive the data
    delay(1);

    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
  }

  // Add a delay to allow DHT sensor to stabilize (2 seconds)
  delay(2000);
}
