/**
 * Hilfsprogramm für die Einstellung von Signal und Timer des PIR Sensors.
 * Augrabe erfolgt über den Serial Monitor.
 */
#include <Arduino.h>
#include "PIRMotionSensor.h"

// PIR Motion Sensor Helper Class
PIRMotionSensor_C pir(PIN4);

void setup() {
  Serial.begin(9600);
  Serial.println("\nPIR Modul. SIGNAL and TIMER adjustment.\n");
  pir.setup();
}

void loop() {
  
  // Read Signal PIN (for demo only)
  int sig = pir.readSignal();
  
  // Serial Monitor
  Serial.print(" CNT: ");
  Serial.print(pir.getAlerts());
  Serial.print(" SIG: ");
  Serial.print(sig);

  // PIR motion detection (if SIG is changed, than ...)
  switch ( pir.detect() ) {
    case 2: // Motion
      Serial.print(" DESC: ");
      Serial.print("MOTION");
      break;
    case 1: // Unlock
      Serial.print(" DESC: ");
      Serial.print("UNLOCK");
      Serial.print(" TIMER ");
      Serial.print(pir.getLockTimer());
      break;
    default: // Nothing changed
      Serial.print(" DESC: ");
      Serial.print("---");
      Serial.print((char) ( 63+rand() % 26) );
      Serial.print("---");
      break;
  }

  Serial.println();
  delay(500);
}