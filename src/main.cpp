#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define TURN_ON 1024

const char *ssid = "Esox_temp";
const char *password = "2829Krenick&";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

double light_index = 1;

void turnOnLineary() {
   if (!light_index) light_index = 1;
   while (light_index < TURN_ON) {
      light_index = light_index * 1.2;
      analogWrite(D2, light_index);
      delay(100);
   }
}

void turnOffLineary() {
   while (light_index > 0) {
      light_index = light_index / 1.2;
      analogWrite(D2, light_index);
      delay(100);
   }
}

void setup() {
   Serial.begin(115200);
   pinMode(D5, INPUT);   // motion sensor
   pinMode(D2, OUTPUT);  // light
   // pinMode(D8, OUTPUT);  // motor
   digitalWrite(D2, LOW);

   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
   }
   timeClient.begin();
   timeClient.setTimeOffset(60 * 60);
   Serial.println(timeClient.getFormattedTime());
}

void loop() {
   int val = digitalRead(D5);
   bool turnOn = false;
   bool printingStatus = false;

   timeClient.update();
   if (timeClient.getHours() > 16 || timeClient.getHours() < 9) {
      while (val == HIGH || turnOn) {
         turnOn = false;
         printingStatus = true;
         Serial.printf("Pohyb byl zaznamenan!\n");
         // digitalWrite(D2, HIGH);
         turnOnLineary();
         Serial.printf("\n");
         delay(30000);

         for (int i = 0; i < 100 && !turnOn; ++i) {
            val = digitalRead(D5);
            if (val == HIGH) {
               turnOn = true;
               Serial.printf("Opet spatren pohyb!\n");
            }
            delay(10);
         }
      }
   }
   if (printingStatus) {
      Serial.printf("Vypinam svetlo.\n");
      turnOffLineary();
   }
}