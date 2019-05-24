#include <Arduino.h>
#include <SignalLED.h>

unsigned long counter = 0;

SignalLED signalLED(6,5);

void setup() {
  Serial.begin(9600);
  signalLED.start();
  pinMode(7, INPUT);     // GND
}

void loop() {
  Serial.print("Serial monitor test: ");
  Serial.println(counter++);
  boolean in = digitalRead(7);
  Serial.print("Kontaktgleis: ");
  Serial.println(in);
  if (digitalRead(7) == HIGH) {
    signalLED.start();
    counter = 0;
    delay(200);
    return;
  }
  
  signalLED.alive(20);
  delay(100);
}
