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
#include <SignalLED.h>

// Counting ticks
unsigned long counter = 0;

const int TICK = 100;
const int WAIT = 500;
const int LATENCY = 50;

// IRremote defines
IRrecv irrecv(11); 
decode_results results; 

unsigned long ir_undefined;

// Initialize SignalLED using PIN 6 (GND on PIN 5)
SignalLED signalLED(6, 5);

void reset() {
  ir_undefined = 0;
  counter = 1;      // 0 würde alive-LED auslösen, was nicht gewünscht ist
}

void setup() {
  Serial.begin(9600);

  // Set pin mode for IR
  pinMode(9, OUTPUT);     // IR +5V
  pinMode(10, OUTPUT);    // IR gnd
  pinMode(11, OUTPUT);    // IR input (see: enableIRIn)

  // Initial pin level for IR
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  // Initial IR in pin
  irrecv.enableIRIn();  

  // First LED 'Hello' 
  signalLED.start();
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
      signalLED.blink(2, 300);
      reset();
      break;
    case 16228447: case 1838327895:
      Serial.println("IR receive: GREEN Button pusched.");
      signalLED.blink(3, 300);
      reset();
      break;
    case 1838336055: 
      Serial.println("IR receive: Start/Stop Button pusched.");
      signalLED.start();
      reset();
      break;
    default: 
      signalLED.panik();
      Serial.println("IR receive: undefined code.");
      ir_undefined = results.value;
      break;
    }
  }

  signalLED.alive();

  delay(TICK);
}
