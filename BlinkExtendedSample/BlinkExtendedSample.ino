/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

// ===================================================================
// Configuration
// =================================================================== 

#define BUILTIN_LED  13

// ===================================================================
// The Blink-Class
// =================================================================== 
 
/**
 * Defines a simple Component using a timer instead delay. 
 */
class Blink {
private:
  int ledPin;
  int interval = 1500;
  int value = LOW;
  int timer = 0;
public:
  Blink() {
    this->timer = 0;
    this->value = LOW;
  }
  
  void setup(int pin, int interval = 1500) {
    this->ledPin = pin;
    this->interval = interval;
    pinMode(ledPin, OUTPUT);
  }
  
  void toggle() {
      value = ( value == HIGH ) ? LOW : HIGH;
      digitalWrite(ledPin, value);
  }
  
  void looper() {
    if ( ++timer >= interval ) {
      timer = 0;
      toggle();
    }
  }
  
};

// ===================================================================
// Arduino Setup and Loop Funtion
// =================================================================== 

Blink blink;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  blink.setup(BUILTIN_LED);
}

// the loop routine runs over and over again forever:
void loop() {
  blink.looper();
  delay(1);
}
