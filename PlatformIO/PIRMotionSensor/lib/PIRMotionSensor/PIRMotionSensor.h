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

  // Zeit bis zum Zurücksetzen des Alert-Status (Lock-Timer)
  unsigned long lc_timer;
  unsigned long lc_start;
  unsigned long lc_stop;

  // Auslesen des Daten-PIN
  int readSignal();

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
  unsigned long getLockTimer();
};
#endif