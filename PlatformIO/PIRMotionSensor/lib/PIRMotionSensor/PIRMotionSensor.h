#ifndef PIRMOTIONSENSOR_H
#define PIRMOTIONSENSOR_H

class PIRMotionSensor_C {

protected:

  // Signal PIN Number eg. PIN4
  int PIN_SIG;

  // Letzter Bewegungsstatus 
  int value;

  // Zählt die Bewegungsalarme
  int counter;

public:

  const int MOTION_ALERT = HIGH;
  const int MOTION_SLEEP = LOW;
  const int PIR_ALERT_SIGNAL = HIGH;
  const int PIR_SLEEP_SIGNAL = LOW;

  PIRMotionSensor_C(int pin_sig);
  void setup();
  int detect(int mode = 0);
  void reset();
  bool locked();

};
#endif