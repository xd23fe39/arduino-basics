/*
  Blink Class Sample - working with classes and timer instead delay
  
  This sample is based on the Blink-Sample and demonstrates the benefit of
  using classes. 
  
  https://github.com/xd23fe39/arduino-basics
  
 */

// ===================================================================
// Configuration
// =================================================================== 

#define BUILTIN_LED  13

// ===================================================================
// The Blink-Class
// =================================================================== 
 
/**
 * Defines a simple kind of component class using a timer instead delay. 
 */
class Blink {
private:
  int ledPin;  // LED Pin number (Digital in/out)
  int value = LOW;  // LED Pin value HIGH or LOW
  int interval = 1500;  // toggle time period in ms 
  int timer = 0; // loop counter
public:
  /**
   * Constructor. Initialize some class attributes.
   */
  Blink() {
    this->timer = 0;
    this->value = LOW;
  }
  
  /**
   * Setup-Method. 
   */
  void setup(int pin, int interval = 1500) {
    this->ledPin = pin;
    this->interval = interval;
    pinMode(ledPin, OUTPUT);
  }
  
  /**
   * Loop-Method. The loop method implement a loop counter (timer)
   * and one or more counter-events. 
   */
  void loop() {
    // call toggle() if counter reached the predefined interval.
    if ( ++timer >= interval ) {
      toggle();
    }
  }
  
  /**
   * Toggle-Method toggle the digital pin between LOW and HIGH.
   */
  void toggle() {
      this->value = ( this->value == HIGH ) ? LOW : HIGH;
      this->timer = 0;
      digitalWrite(ledPin, value);
  }  
};

// ===================================================================
// Arduino Setup and Loop Funtion
// =================================================================== 

Blink blink;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the object and setup a LED Pin number.
  blink.setup(BUILTIN_LED);
}

// the loop routine runs over and over again forever:
void loop() {
  // call the loop-method of the object
  blink.loop();
  // wait for 1ms until next loop
  delay(1);
}
