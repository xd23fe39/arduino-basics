#include <Arduino.h>
#include <SignalLED.h>
#include <AnalogReader.h>

unsigned long counter = 0;
int analog_in = analogRead(A2), analog_merke;

SignalLED signalLED(6,5);
AnalogReader analogReader;

void setup() {
  Serial.begin(9600);

  // Bauteil wird mit allen drei PINs in UNO eingesteckt
  analogReader.setup(A2, A0, A4);

  Serial.println("Analog Input Demo");
  signalLED.start();
}

void loop() {
    
  if (analogReader.trim()) { 
    Serial.print("Analog input (A2): ");
    Serial.print(analogReader.value());
    Serial.print(" Prozent: ");
    Serial.println(analogReader.value(0, 100));
    analog_merke = analog_in;
  }

  // lässt alle 200 Ticks die LED für value() Millisekunden leuchten
  signalLED.alive(200, analogReader.value(0, 1000));

  delay(10);
}
