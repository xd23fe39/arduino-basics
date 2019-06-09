
#include <Arduino.h>
#include "PIRMotionSensor.h"

PIRMotionSensor_C::PIRMotionSensor_C(int pin_sig) {
  this->PIN_SIG = pin_sig;
}

void PIRMotionSensor_C::setup() {
  this->reset();  
}
  
int PIRMotionSensor_C::detect(int mode = 0) {
  int in = digitalRead(this->PIN_SIG);
  // PIR wechselt in den Alert-Modus (Alert setzen)
  if ( this->value == MOTION_SLEEP && in == PIR_ALERT_SIGNAL ) {
    this->value = MOTION_ALERT;    // Save motion alert 
    this->counter++;            // Detection counter
    if (mode == 0) {
      return MOTION_ALERT;
    }
  }
  // PIR wechselt wieder in den Sleep-Modus (Alert löschen)
  if ( this->value == MOTION_ALERT && in == PIR_SLEEP_SIGNAL ) {
    this->value = MOTION_SLEEP;
  }
  if ( this->value == in ) {
    // Nothing was changed...
  }
  if (mode == 0) {
    return MOTION_SLEEP;
  }
  else {
    return this->value;
  }
  
}

bool PIRMotionSensor_C::locked() {
  int in = digitalRead(this->PIN_SIG);
  return (in == PIR_ALERT_SIGNAL);
}

void PIRMotionSensor_C::reset()  {
  pinMode(this->PIN_SIG, INPUT);
  this->value = PIRMotionSensor_C::MOTION_SLEEP;
  this->counter = 0;
}
