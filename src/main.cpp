#include <Arduino.h>

void setup() {
   Serial.begin(115200);
   pinMode(D5, INPUT);   // motion sensor
   pinMode(D2, OUTPUT);  // light
   // pinMode(D8, OUTPUT);  // motor

   digitalWrite(D2, LOW);
}

void loop() {
   int val = digitalRead(D5);
   bool turnOn = false;
   bool printingStatus = false;

   while (val == HIGH || turnOn) {
      turnOn = false;
      printingStatus = true;
      Serial.printf("Pohyb byl zaznamenan!\n");
      digitalWrite(D2, HIGH);
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
   if (printingStatus) {
      Serial.printf("Vypinam svetlo.\n");
      digitalWrite(D2, LOW);
   }
}