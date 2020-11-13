#include <Arduino.h>

#define PIR_DATA 4

unsigned long pt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIR_DATA, INPUT);
}

void loop() {
  int val = digitalRead(PIR_DATA);
  Serial.print(pt);
  Serial.print(" ");
  Serial.println(val);
  delay(500);
  pt++;
}