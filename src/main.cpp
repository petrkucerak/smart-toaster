#include <Arduino.h>

void setup() {
   Serial.begin(115200);
   pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
   digitalWrite(LED_BUILTIN, HIGH);
   Serial.printf("Light on!\n");
   delay(5000);
   Serial.printf("Light off!\n");
   digitalWrite(LED_BUILTIN, LOW);
   delay(5000);
}