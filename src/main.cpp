#include <Arduino.h>
#include <ArduinoWiFiServer.h>

#ifndef STASSID
#define STASSID "Esox_temp"
#define STAPSK "2829Krenick&"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

ArduinoWiFiServer server(2323);

void buildin_led_loop(){
   digitalWrite(LED_BUILTIN, HIGH);
   // Serial.printf("Light on!\n");
   delay(1000);
   // Serial.printf("Light off!\n");
   digitalWrite(LED_BUILTIN, LOW);
   delay(1000);
}

void simply_server(){

}

void setup() {
   Serial.begin(115200);
   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, LOW);

   // Connect to wify
   Serial.printf("Connecting to %s\n", ssid);
   Serial.printf("with password %s\n", password);

   WiFi.begin(ssid, password);

   while(WiFi.status() != WL_CONNECTED){
      // delay(500);
      buildin_led_loop();
      Serial.print(".");
   }

   server.begin();

   IPAddress ip = WiFi.localIP();
   Serial.print("Connected on the wifi network. For access the server, connect with Telnet client to ");
   Serial.print(ip);
   Serial.printf(".\n");
}

void loop() {
   // buildin_led_loop();
   Serial.print("CONNNECTED!\n");
}