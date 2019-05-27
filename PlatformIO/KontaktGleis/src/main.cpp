#include <Arduino.h>
#include <SignalLED.h>

class Kontaktschaltung {

protected:

  SignalLED *signalLED;

  // Counter
  unsigned counter = 0;

  // PIN Layout
  uint8_t pin_sig = 7;

public:

  Kontaktschaltung(SignalLED *signalLED = NULL) {
    this->signalLED = signalLED;
  }

  ~Kontaktschaltung() {
    free(signalLED);
  }

  void init() {
  }

  boolean read() {
    return digitalRead(pin_sig);    
  }

  void alive() {
    if (read() == HIGH) {
      if ( signalLED )
        signalLED->blink(1, 500);
      counter = 0;
    }

    // Zähler
    counter++;
  }

};

SignalLED signalLED(6,5);
Kontaktschaltung schalter(&signalLED);

void setup() {
  Serial.begin(9600);
  schalter.init();
  signalLED.start();
}

void loop() {
  schalter.alive();
  signalLED.alive();

  // Warte 100ms
  delay(100);
}
