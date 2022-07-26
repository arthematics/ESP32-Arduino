/*********
  Artem Pokintelitsa

  Name:
  ESP32 asynchronous HTTP server

  Description:
  An asynchronous HTTP web server configuration on the ESP32 microcontroller.

  In Soft Access Point mode, or AP mode, the ESP32 provides a Wi-Fi connection
  for external devices. The code in the loop() function definition allows to
  get the number of Wi-Fi stations connected to the network hosted by the ESP32.

  Acknowledgements:
  Neil Cameron
  Alexander Mayorov aka AlexGyver (alexgyver.ru)
  Nuno Santos (techtutorialsx.com)
  Rui Santos and Sara Santos (randomnerdtutorials.com)
*********/

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

/*
  Declare a variable of class AsyncWebServer. It will be used to set up
  the asynchronous HTTP server. HTTP communication takes place over TCP/IP
  connections. This requires a port number where the server will be listening.
  The default port is 80.
*/
AsyncWebServer server(80);

/*
  Create a start web page. The PROGMEM utility allows to store the web page
  code in flash (program) memory instead of SRAM. The PROGMEM keyword is
  a variable modifier and it refers to the <avr/pgmspace.h> library.

  The R"rawliteral(....)rawliteral" construction allows to treat everything
  between the round brackets as a raw string. This is a practical way to
  handle long strings containing quotation marks.
*/
const char startPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<link rel="icon" href="data:,">
<title>ESP32 start page</title>
</head>
<body>
<h1 align="center">ESP32 start page</h1>
</body>
</html>
)rawliteral";

char ssidAP[]     = "ESP32 Wi-Fi LAN";  // WLAN SSID
char passwordAP[] = "12345678";         // WLAN password
IPAddress local_ip(192, 168, 2, 3);     // pre-defined IP address values
IPAddress gateway(192, 168, 2, 3);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  // Technical delay for smooth board connecting and serial monitor launch
  delay(7000);

  // Start a serial communication
  Serial.begin(115200);
  Serial.println("\nSerial communication started.\n");
  
  // Information about AP setup
  Serial.println("Setting AP (Access Point)…\n");
  
  WiFi.mode(WIFI_AP); // set the ESP32 as an access point (AP mode)
  delay(1000);
  WiFi.softAP(ssidAP, passwordAP); // initialize Wi-Fi with predefined IP address
  WiFi.softAPConfig(local_ip, gateway , subnet);
  Serial.println("Wi-Fi connected.");

  // Print the local IP address
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.println();

  // Load the start web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request -> send_P(200, "text/html", startPage);
  });

  // The start web page status
  Serial.println("Start page is ready to load.\n");

  server.begin(); // initialize the asynchronous HTTP server
}

void loop() {
  /*
  The softAPgetStationNum method returns the number of stations connected to
  the Wi-Fi local network. The result will be printed to the serial port.
  */
  Serial.print("Stations connected: ");
  Serial.println(WiFi.softAPgetStationNum());
  Serial.println();
  delay(20000);
}
