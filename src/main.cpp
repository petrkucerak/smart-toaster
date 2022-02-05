#include <Arduino.h>

#define TURN_ON 1024

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
      if (light_index < 10) {
         light_index = 10;
         while (light_index != 0) {
            --light_index;
            analogWrite(D2, light_index);
            delay(100);
         }
      }
   }
}

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

   if (printingStatus) {
      Serial.printf("Vypinam svetlo.\n");
      turnOffLineary();
   }
}