class Kontaktschalter {

protected:

  SignalLED *signalLED;

  // Counter
  unsigned counter = 0;
  unsigned pushed = 0;

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
      counter++;
      if (counter == 1) pushed++;
    }
    else
        counter = 0;      // Zähler nullen

    return state;
  }

  int getState() {
    return state;
  }

  int getCounter() {
    return counter;
  }

  int getPushed() {
    return pushed;
  }

};
