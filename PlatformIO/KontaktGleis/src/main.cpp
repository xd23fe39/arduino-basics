#include <Arduino.h>
#include <SignalLED.h>
#include <Kontaktschalter.h>

const uint8_t PIN_LED_VCC = 6;
const uint8_t PIN_LED_GND = 5;
const uint8_t PIN_BTN_SIG = 7;

SignalLED signalLED(PIN_LED_VCC, PIN_LED_GND);
Kontaktschalter schalter(PIN_BTN_SIG);

void setup() {
  // Serial Monitor
  Serial.begin(9600);

  // Initialize
  schalter.init();
  signalLED.start();

  // Ende von Setup melden
  Serial.println("\nKontaktschalter bereit.\n");
}

void loop() {
  // LED alive blink signal
  signalLED.alive();
  
  // Kontaktschalter abfragen und auslösen
  if ( schalter.alive() == HIGH ) {
    // Auslöseanzeige über Serial Monitor
    Serial.print("Kontaktschalter: ");
    Serial.print(" | Pushed: ");
    Serial.print(schalter.getPushed());
    Serial.print(" | Zähler: ");
    Serial.print(schalter.getCounter());
    Serial.print(" | Zustand: ");
    Serial.print(schalter.getState());
    Serial.println(" #");
    // Blinksignal ausgeben
    signalLED.blink(1, 100);    // Leuchtdauer 100ms
  }

  // Wartezyklus 100ms
  delay(100);
}
