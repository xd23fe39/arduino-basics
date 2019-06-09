
#include <Arduino.h>
#include "PIRMotionSensor.h"

PIRMotionSensor_C::PIRMotionSensor_C(int pin_sig) {
  this->PIN_SIG = pin_sig;
}

void PIRMotionSensor_C::setup() {
  this->reset();  
}
  
int PIRMotionSensor_C::detect(int mode = 0) {
  int in = readSignal();
  // PIR wechselt in den Alert-Modus (Alert setzen)
  if ( this->value == MOTION_SLEEP && in == PIR_ALERT_SIGNAL ) {
    this->value = MOTION_ALERT;    // Save motion alert 
    this->counter++;            // Detection counter
    this->lc_start = millis();
    if (mode == 0) {
      return MOTION_ALERT;
    }
  }
  // PIR wechselt wieder in den Sleep-Modus (Alert löschen)
  if ( this->value == MOTION_ALERT && in == PIR_SLEEP_SIGNAL ) {
    this->value = MOTION_SLEEP;
    this->lc_stop = millis();
    this->lc_timer = lc_stop - lc_start;
  }
  if ( this->value == in ) {
    // Nothing is changed...
  }
  if (mode == 0) {
    return MOTION_SLEEP;
  }
  else {
    return this->value;
  }
  
}

bool PIRMotionSensor_C::locked() {
  int in = readSignal();
  return (in == PIR_ALERT_SIGNAL);
}

unsigned long PIRMotionSensor_C::getLockTimer() {
  return this->lc_timer;
}

void PIRMotionSensor_C::reset()  {
  pinMode(this->PIN_SIG, INPUT);
  this->value = PIRMotionSensor_C::MOTION_SLEEP;
  this->counter = 0;
  // Zurücksetzen der Lock Timer Daten
  this->lc_timer = 0;
  this->lc_start = 0;
  this->lc_stop = 0;
}

/*

Protected methods

*/

int PIRMotionSensor_C::readSignal()  {
  return digitalRead(this->PIN_SIG);
}
