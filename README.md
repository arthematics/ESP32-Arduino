# ESP32_Arduino

## Projects:

* **ESP32 asynchronous HTTP server**
  
  Description:

  An asynchronous HTTP server configuration on the ESP32 microcontroller. In Access Point mode, or AP mode, the ESP32 provides a Wi-Fi connection for external devices. The code in the loop() function definition allows to get the number of Wi-Fi stations connected to the network hosted by the ESP32.
  
  A static IP address is used. Thus, the ESP32 does not use DHCP to get IP parameters, and they must be configured directly during the implementation of the softAPConfig method.
  
  Notes:
  
  Training project. The Wi-Fi API is implemented using libraries from [Arduino core for the ESP32](https://github.com/espressif/arduino-esp32).

* **ESP32 web server for camera control**
  
  Description:

## Files:

* **template.ino**
  
  Description:

  A practical template based on [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with some modification for Arduino IDE.
