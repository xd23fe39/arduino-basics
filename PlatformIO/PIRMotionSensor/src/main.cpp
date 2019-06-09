#include <Arduino.h>
#include "PIRMotionSensor.h"

PIRMotionSensor_C pir(PIN4);

void setup() {
  // put your setup code here, to run once:
  pir.setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( pir.detect() ) {
    for (int i = 0; i <= 3; i++) { 
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  }
}