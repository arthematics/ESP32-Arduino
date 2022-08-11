/*****************************************************************************80
  Artem Pokintelitsa

  Name:
  ESP32 asynchronous HTTP server

  Description:
  An asynchronous HTTP web server configuration on the ESP32 microcontroller.

  In Access Point mode, or AP mode, the ESP32 provides a Wi-Fi connection
  for external devices. The code in the loop() function definition allows to
  get the number of Wi-Fi stations connected to the network hosted by the ESP32.
  
  A static IP address is used. Thus, the ESP32 does not use DHCP to get IP
  parameters, and they must be configured directly during the implementation of
  the softAPConfig method.
  
  Notes:
  Training project. The Wi-Fi API is implemented using libraries from Arduino
  core for the ESP32.

  Acknowledgements:
  Neil Cameron
  Alexander Mayorov aka AlexGyver (alexgyver.ru)
  Nuno Santos (techtutorialsx.com)
  Rui Santos and Sara Santos (randomnerdtutorials.com)
*******************************************************************************/

/*
  DEFINED CONSTANTS AND SETTINGS

  Create a start web page. The PROGMEM utility allows to store the web page
  code in flash (program) memory instead of SRAM. The PROGMEM keyword is
  a variable modifier and it refers to the <avr/pgmspace.h> library.

  The R"rawliteral(....)rawliteral" construction allows to treat everything
  between the round brackets as a raw string. This is a practical way to
  handle long strings containing quotation marks.
*/
const char kStartPage[] PROGMEM = R"rawliteral(
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

/*
  LIBRARIES AND FILES
*/
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
  VARIABLES

  A gateway is a network node that serves as an access point to another network.
  A subnet mask is a 32-bit number that masks an IP address and divides the IP
  address into network address and host address.
  The address range assignable to hosts is from 192.168.10.1 to 192.168.10.254
  because the TCP/IP defines the addresses 192.168.10.0 and 192.168.10.255 for
  special functions.
  
  Note: If the ESP32 module is used in STA mode, it is needed to specify the DNS
  IP address as follows IPAddress dns_ip(192, 168, 10, 1). The IP address of the
  DNS server should be used when a project involves converting domain names into
  IP addresses.
*/
char wifi_ssid[14] = "ESP32 NETWORK";    // set Wi-Fi LAN SSID
char wifi_password[9] = "12345678";      // set Wi-Fi LAN password
IPAddress local_ip(192, 168, 10, 10);    // set the static IP address
IPAddress gateway_ip(192, 168, 10, 1);   // set the gateway IP address
IPAddress subnet_mask(255, 255, 255, 0); // set the subnet mask of the network

/*
  SETUP FUNCTION
*/
void setup() {
  // Technical delay for smooth board connecting and serial monitor launch
  delay(7000);

  // Start a serial communication
  Serial.begin(115200);
  Serial.println("\nSerial communication started.\n");
  
  // Information about Access Point setup
  Serial.println("Setting Access Point (AP)…\n");
  
  /*
    Set the ESP32 as an Access Point (AP mode) and configure it with the
    predefined parameters. Wi-Fi clients (stations) can connect to the Access
    Point using the network credentials defined above.
  */
  WiFi.mode(WIFI_AP); // set the AP mode
  delay(1000);
  WiFi.softAP(wifi_ssid, wifi_password); // initialize Wi-Fi LAN
  WiFi.softAPConfig(local_ip, gateway_ip, subnet_mask);
  Serial.println("ESP32 is configured as an Access Point.\n");

  // Print the local IP address
  IPAddress my_local_ip = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(my_local_ip);
  Serial.println();

  // Load the start web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request -> send_P(200, "text/html", kStartPage);
  });

  // The start web page status
  Serial.println("Start page is ready to load.\n");
  
  // Information about how to access the start page
  Serial.print("The start web page is available at http://");
  Serial.print(my_local_ip);
  Serial.print("/\n\n");

  server.begin(); // initialize the asynchronous HTTP server
}

/*
  LOOP FUNCTION
  
  The softAPgetStationNum method returns the number of stations connected to
  the Wi-Fi local network. The result will be printed to the serial monitor.
*/
void loop() {
  Serial.print("Stations connected: ");
  Serial.println(WiFi.softAPgetStationNum());
  Serial.println();
  delay(20000);
}
