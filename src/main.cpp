#include <Arduino.h>

void setup(){
   Serial.begin(115200);
}

void loop(){
   Serial.print("Test!\n");
   delay(10000);
}