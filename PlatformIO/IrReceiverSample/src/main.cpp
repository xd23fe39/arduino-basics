/**
 * 
 * PlatformIO: Install library using PlatformIO
 * - Search for: IRremote by Rafi Khan 
 * 
 * Download IRremote Arduino Library on Github:
 * - URL: https://github.com/z3t0/Arduino-IRremote
 *
 */

#include <Arduino.h>
#include <IRremote.h>

// Counting ticks
unsigned long counter = 0;

const int TICK = 100;
const int WAIT = 500;
const int LATENCY = 50;

// IRremote defines
IRrecv irrecv(11); 
decode_results results; 

unsigned long ir_undefined;

/**
 * Lässt die LED auf Pin pin cnt-Mal blinken.
 */
void blink(int pin, int cnt, int rate = 500) {
  digitalWrite(pin, LOW);
  delay(LATENCY);
  for (int i = 0; i < cnt; i++) {
    digitalWrite(pin, HIGH);
    delay(rate);
    digitalWrite(pin, LOW);
    delay(rate);
  }
}

/**
 * Lässt die LED auf Pin pin 'hektisch' blinken.
 */
void panik(int pin, int cnt = 10, int rate = 50) {
  blink(pin, cnt, rate);
}

void alive(int pin, int rate = 50) {
  digitalWrite(pin, LOW);
  delay(LATENCY);
  digitalWrite(pin, HIGH);
  delay(rate);
  digitalWrite(pin, LOW);
}

void start(int pin, int rate = 800) {
  digitalWrite(pin, LOW);
  delay(LATENCY);
  digitalWrite(pin, HIGH);
  delay(rate);
  digitalWrite(pin, LOW);
  delay(500);
  digitalWrite(pin, HIGH);
  delay(rate);
  digitalWrite(pin, LOW);
  delay(500);
  digitalWrite(pin, HIGH);
  delay(200);
  digitalWrite(pin, LOW);
  delay(WAIT);
}

void reset() {
  ir_undefined = 0;
  counter = 1;      // 0 würde alive-LED auslösen, was nicht gewünscht ist
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

  if (ir_undefined) {
    Serial.print("IRremote: last undefined code: ");
    Serial.print(ir_undefined);
  }
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
    case 16195807: case 1838295255:
      Serial.println("IR receive: RED Button pusched.");
      blink(6, 2, 300);
      reset();
      break;
    case 16228447: case 1838327895:
      Serial.println("IR receive: GREEN Button pusched.");
      blink(6, 3, 300);
      reset();
      break;
    case 1838336055: 
      Serial.println("IR receive: Start/Stop Button pusched.");
      start(6);
      reset();
      break;
    default: 
      panik(6);
      Serial.println("IR receive: undefined code.");
      ir_undefined = results.value;
      break;
    }
  }

  if (counter % 20 == 0)
    alive(6);

  delay(TICK);
}
