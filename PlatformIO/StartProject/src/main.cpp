#include <Arduino.h>

unsigned long counter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Serial monitor test: ");
  Serial.println(counter++);
  delay(2000);
}
