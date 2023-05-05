#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

//#define DEBUG_WIFI
// const char* ssid = "Mi 9 Lite";
// const char* password = "12345678@";

const char* host = "192.168.43.34"; // IP address of the computer running the Python program

const int port = 1234;

WiFiServer server1(port);
WiFiClient client;


// void setupWifi() {

//   Serial.begin(9600);

//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     #ifdef DEBUG_WIFI
//     Serial.println("Connecting to WiFi...");
//     #endif
//   }
//    #ifdef DEBUG_WIFI
//   Serial.println("Connected to WiFi");
//   #endif

// }

void sendData(int16_t data) {
  
   if (client.connect(host, port)) {
    client.write((uint8_t*)&data, sizeof(data));
    #ifdef DEBUG_WIFI
    Serial.println(data);
    #endif
    //delay(10); // delay to avoid overloading the server
  } else {
    client = server1.available();
    #ifdef DEBUG_WIFI
    Serial.println("client not connected");
    #endif
  }
  
}
