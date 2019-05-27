class Kontaktschalter {

protected:

  SignalLED *signalLED;

  // Counter
  unsigned counter = 0;

  // PIN Layout
  uint8_t pin_sig = 7;

  // PIN Status;
  int state;

public:

  Kontaktschalter(uint8_t pin, SignalLED *signalLED = NULL) {
    this->signalLED = signalLED;
    this->pin_sig = pin;
    state = read();
  }

  ~Kontaktschalter() {
    free(signalLED);
  }

  void init() {
  }

  boolean read() {
    return digitalRead(pin_sig);    
  }

  int alive() {
    state = read();
    if (state == HIGH) {
      if ( signalLED )
        signalLED->blink(1, 500);
      counter = 0;
    }

    // Zähler
    counter++;

    return state;
  }

  int getState() {
    return state;
  }

};
