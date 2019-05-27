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
  Serial.println("Kontaktschalter bereit.");
}

void loop() {
  // LED alive blink signal
  signalLED.alive();
  
  // Kontaktschalter abfragen und auslösen
  if ( schalter.alive() == HIGH ) {
    // Auslöseanzeige über Serial Monitor
    Serial.print("Kontaktschalter: ");
    Serial.println(schalter.getState());
    // Blinksignal ausgeben
    signalLED.blink(1, 500);    // Leuchtdauer 500ms
  }

  // Wartezyklus 100ms
  delay(100);
}
