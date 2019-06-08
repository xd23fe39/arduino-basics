/* Arduino Serial Interface Demo
 *
 * You only need:
 * 
 * - Arduino Board
 * - Serial Cable
 * 
 * Connect your Arduino to your computer and upload the sketch.
 * 
 * Open a terminal session on your computer.
 * 
 * Type:
 *   echo "Hello" > /dev/ttyUSB0 
 *
 * Magic!
 */

#include <Arduino.h>

const int BAUD = 9600;    // 9600
const int EOL = 10;

unsigned long counter = 0;
int in;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  Serial.println("\nArduino NANO Atmel328 Setup");
  Serial.print("Version: ");
  Serial.println(__VERSION__);
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( Serial.available() ) {
    in = Serial.read();
    if ( in == EOL ) {
      Serial.println(" ---- ");
    }
    else {
      Serial.print(" Serial Read: ");
      Serial.print(in);
      Serial.print(" ");
      Serial.print((char)in);
      Serial.println();
    }
  }
  if ( Serial.availableForWrite() ) {
    Serial.print(" Tick");
    delay(100);
  }
  counter++;
}