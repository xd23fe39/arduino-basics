/**
 * Hilfsprogramm für die Einstellung von Signal und Timer des PIR Sensors.
 * Augrabe erfolgt über den Serial Monitor.
 */
#include <Arduino.h>
#include "PIRMotionSensor.h"

// PIR Motion Sensor Helper Class
PIRMotionSensor_C pir(PIN4);

unsigned long timer_blink = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("\nP-I-R Modul. SIGNAL and TIMER adjustment.\n");
  Serial.println("\nP-I-R is ready....\n");
  pir.setup();
}

void dump_serial(PIRMotionSensor_C p, String text) {
  char buffer[12];
  sprintf(buffer, "%.11ld", p.getTimer());
  Serial.print("TIME: ");
  Serial.print(buffer);
  sprintf(buffer, "%.6ld", p.getTimerStop());
  Serial.print(" WAIT: ");
  Serial.print(buffer);
  Serial.print(" COUNT: ");
  Serial.print(p.getAlerts());
  Serial.print(" SIGN: ");
  Serial.print(p.readSignal());
  Serial.print(" DESC: ");
  Serial.print(text);
  Serial.println();  
}

void loop() {
  
  // Read Signal PIN (for demo only)
  int sig = pir.readSignal();
  
  // PIR motion detection (if SIG is changed, than ...)
  switch ( pir.detect() ) {
    case 2: // Motion
      dump_serial(pir, "MOTION ALERT");
    break;
    case 1: // Unlock
      dump_serial(pir, "UNLOCK");
      break;
    default: // Nothing changed
      if (pir.locked()) {
        dump_serial(pir, "LOCKED");
      }
      while (pir.locked()) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
      }
      break;
  }

  // alle 2 Sekunden blinkt die LED sehr kurz auf => ALIVE
  if (timer_blink == 2000) { 
    timer_blink = 0;
    digitalWrite(LED_BUILTIN, HIGH);
    delay(20);
    digitalWrite(LED_BUILTIN, LOW);
    delay(20);
  }

  // Aufgrund der kurzen delay-Zeiten reagiert das Programm sehr schnell
  // auf Veränderungen.
  delay(1);
  timer_blink++;
}