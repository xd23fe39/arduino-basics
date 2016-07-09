/* Sketch: IRUniversalMonitor
 * 
 * Required:
 * http://z3t0.github.io/Arduino-IRremote/
 * https://github.com/z3t0/Arduino-IRremote
 * 
 * Tested on: Arduino Nano Clone ATmega 328P v3 
 * 
 */
 
#include <IRremote.h>

// IR PIN layout
#define PIN_IR_RECV  11

// IR Receiver Objekt
IRrecv irrecv(PIN_IR_RECV);

decode_results ir_results;

static long count = 0;
static long ignore = 0;

void printSerial(decode_results& ir_results) {
    Serial.print(count);
    Serial.print("; ");
    Serial.print(ir_results.decode_type);
    Serial.print("; ");
    Serial.print(ir_results.value, HEX);
    Serial.print("; ");
    Serial.print(ir_results.value);
    Serial.print("; ");
    Serial.print(ignore);
    Serial.println();
    count++;
}

void setup() {
  // Start Serial Monitor 
  Serial.begin(9600);
  // Initial output
  Serial.println("IRUniversalMonitor is ready:");
  Serial.println("Pos; Decode Type; Value; Decimal; Ignore ");
  // IR receiver starten
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&ir_results)) {
    // Print on serial monitor
    if ( ir_results.value != 0xffffffff )
      printSerial(ir_results);
    else
      ignore++;
    // Receive the next datagram
    irrecv.resume();
    // Waiting/Sleeping for a while 
    delay(500);
  }
}

