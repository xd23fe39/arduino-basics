
#include <Arduino.h>
#include "PIRMotionSensor.h"

PIRMotionSensor_C::PIRMotionSensor_C(int pin_sig) {
  this->PIN_SIG = pin_sig;
}

void PIRMotionSensor_C::setup() {
  this->reset();  
}
  
int PIRMotionSensor_C::detect() {
  int in = readSignal();
  // PIR erkennt Bewegung => MOTION_ALERT
  if ( this->value == MOTION_SLEEP && in == PIR_ALERT_SIGNAL ) {
    this->value = MOTION_ALERT;    // Save motion alert 
    this->counter++;            // Detection counter
    this->lc_timer = millis();
    this->lc_start = lc_timer;
    this->lc_stop = 0;
    return 2;
  }
  // PIR Lock wird wieder aufgehoben => MOTION_SLEEP
  if ( this->value == MOTION_ALERT && in == PIR_SLEEP_SIGNAL ) {
    this->value = MOTION_SLEEP;
    this->lc_timer = millis();
    this->lc_stop = lc_timer - lc_start;
    return 1;
  }
  // Keine Änderung erkannt
  this->lc_timer = millis();
  return 0;  
}

bool PIRMotionSensor_C::locked() {
  int in = readSignal();
  return (in == PIR_ALERT_SIGNAL);
}

unsigned long PIRMotionSensor_C::getTimer() {
  return this->lc_timer;
}

unsigned long PIRMotionSensor_C::getTimerStop() {
  return this->lc_stop;
}

int PIRMotionSensor_C::getAlerts() {
  return this->counter;
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
