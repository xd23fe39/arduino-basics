/**
 * 
 * Download IRremote Arduino Library:
 * https://github.com/z3t0/Arduino-IRremote
 *
 */

#include <Arduino.h>
#include <IRremote.h>

unsigned long counter = 0;

// IRremote defines
IRrecv irrecv(11); 
decode_results results; 

unsigned long ir_undefined;

/**
 * Lässt die LED auf Pin pin 'hektisch' blinken.
 */
void panik(int pin, int cnt = 10, int rate = 50) {
  for (int i=0; i<cnt; i++) {
    digitalWrite(pin, LOW);
    delay(rate);
    digitalWrite(pin, HIGH);
    delay(rate);
  }
  digitalWrite(pin, LOW);
}


/**
 * Lässt die LED auf Pin pin cnt-Mal blinken.
 */
void blink(int pin, int cnt, int rate = 500) {
  digitalWrite(pin, LOW);
  delay(1000);
  for (int i = 0; i < cnt; i++) {
    digitalWrite(pin, HIGH);
    delay(rate);
    digitalWrite(pin, LOW);
    delay(500);
  }
}

void setup() {
  Serial.begin(9600);

  // Set LED pin mode
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  // Set pin mode for IR
  pinMode(9, OUTPUT);     // IR +5V
  pinMode(10, OUTPUT);    // IR gnd
  pinMode(11, OUTPUT);    // IR input (see: enableIRIn)

  // Initial LED pin level
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);

  // Initial pin level for IR
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  // Initial IR in pin
  irrecv.enableIRIn();  

}

void loop() {
  Serial.print("IRremote: last undefined code: ");
  Serial.print(ir_undefined);
  Serial.print(". Serial monitor test: ");
  Serial.println(counter++);

  // IRremote receive and decode 
  if (irrecv.decode(&results)) {
    Serial.print("IR receive: ");
    Serial.println(results.value, DEC);
    irrecv.resume();

    switch(results.value) {
    case 0:
      break;
    case 16195807: 
      Serial.println("IR receive: RED Button pusched.");
      blink(6, 2);
      break;
    case 16228447:
      Serial.println("IR receive: GREEN Button pusched.");
      blink(6, 3);
      break;
    default: 
      panik(6);
      Serial.println("IR receive: undefined code.");
      ir_undefined = results.value;
      break;
    }
  }

  digitalWrite(6, LOW);
  delay(900);
  digitalWrite(6, HIGH);
  delay(100);
}
