class SignalLED {

  protected:

    const int WAIT = 500;
    const int LATENCY = 50;

  public:

    int led_pin = 6;
    int led_gnd = 5;

    long counter = 0;

    SignalLED(int pin_led, int pin_gnd) {
      this->setup(pin_led, pin_gnd);
    }

    void setup(int pin_led, int pin_gnd = 0) {
      // Initialize
      this->led_pin = pin_led;
      this->led_gnd = pin_gnd; 
      // PINs for LED
      if (pin_gnd) { 
        pinMode(pin_gnd, OUTPUT);     // GND
        digitalWrite(pin_gnd, LOW); 
      }
      pinMode(pin_led, OUTPUT);       // +5V
      digitalWrite(pin_led, LOW);
    }

    void blink(int cnt, int rate = 500) {
      digitalWrite(this->led_pin, LOW);
      delay(this->LATENCY);
      for (int i = 0; i < cnt; i++) {
        digitalWrite(this->led_pin, HIGH);
        delay(rate);
        digitalWrite(this->led_pin, LOW);
        delay(rate);
      }
    }

  /**
   * Lässt die LED auf Pin pin 'hektisch' blinken.
   */
  void panik(int cnt = 10, int rate = 50) {
    this->blink(cnt, rate);
  }

  void alive(int divisor = 20, int ms = 20) {
    if (this->counter % divisor == 0) {
      digitalWrite(this->led_pin, LOW);
      delay(this->LATENCY);
      digitalWrite(this->led_pin, HIGH);
      delay(ms);
      digitalWrite(this->led_pin, LOW);
    }
    this->counter++;
  }

  void start(int rate = 800) {
    digitalWrite(this->led_pin, LOW);
    delay(this->LATENCY);
    digitalWrite(this->led_pin, HIGH);
    delay(rate);
    digitalWrite(this->led_pin, LOW);
    delay(500);
    digitalWrite(this->led_pin, HIGH);
    delay(rate);
    digitalWrite(this->led_pin, LOW);
    delay(500);
    digitalWrite(this->led_pin, HIGH);
    delay(200);
    digitalWrite(this->led_pin, LOW);
    delay(this->WAIT);
    this->reset();
  }

  void reset() {
    this->counter = 1;      // 0 würde alive-LED auslösen, was nicht gewünscht ist
  }

};
