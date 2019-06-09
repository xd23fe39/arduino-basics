#include <Arduino.h>
#include "PIRMotionSensor.h"

PIRMotionSensor_C pir(PIN4);

void setup() {
  pir.setup();
}

void loop() {
  if ( pir.detect() ) {
    while (pir.locked()) { 
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  }
}