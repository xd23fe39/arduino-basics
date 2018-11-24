/*
  Beleuchtung für Weihnachtsdorf 3V/0.6W (10 LEDs * 0.06W)
  
  Basiert auf dem VBeispiel:

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
  https://www.arduino.cc/reference/en/
*/

#define VERSION "1.0"

#define __DEBUG_SERIAL__ 

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 300;        // value between 0 (0V) and 500 (5V)
int outputValue = 0;          // calculate it 0..255
float shiftValue = 1.09;       // shift output 1.1 = +10%

int  sleep = 20;
unsigned long ticker = 0;
unsigned long t_lap = 0;
unsigned long t_now = 0;

unsigned long tc_hou = 0;
unsigned long tc_min = 0;
unsigned long tc_sec = 0;
unsigned long tc_mil = 0;

void setup() {
  #if defined (__DEBUG_SERIAL__)
    // initialize serial communications at 9600 bps:
    Serial.begin(9600);
    Serial.print("Debug Serial: ON; Version: ");
    Serial.print(VERSION);
    Serial.println();
  #endif
}

/**
 * Zentrale Funktion des Timers.
 */
unsigned long tick() {  
  // Vergangene Millisekunden seit Systemreset
  t_lap = t_now;      // Sichere den alten millis-Wert
  t_now = millis();   // Hole den aktuellen millis-Wert (1s = 1000ms)

  // Umrechnung von t_lap (Zwischenzeit)
  tc_hou = int(t_lap / 3600000) % 24;   // Zeituhr Umrechnung in Stunden
  tc_min = int(t_lap / 60000) % 60;     // Zeituhr Umrechnung in Minuten
  tc_sec = int(t_lap / 1000) % 60;      // Zeituhr Umrechnung in Sekunden
  tc_mil = int(t_lap % 1000) % 1000;    // Zeituhr Umrechnung in Millisekunden

  // Serial Debug
  #if defined (__DEBUG_SERIAL__)
    Serial.print("ticker = ");
    Serial.print(ticker);
    Serial.print("\t ");
    Serial.print("t_lap = ");
    Serial.print(t_lap);
    Serial.print("\t ");  
    Serial.print("t_now = ");
    Serial.print(t_now);
    Serial.print("\t ");  
    Serial.print("TC: ");
    Serial.print(tc_hou);
    Serial.print(" h ");
    Serial.print(tc_min);
    Serial.print(" min ");
    Serial.print(tc_sec);
    Serial.print(" sec ");
    Serial.print(tc_mil);
    Serial.print(" ms.");
    Serial.print("\t ");
  #endif

  ticker += 1;

  return t_now;
}

/**
 * Print Serial Output 
 */
void psout() {
  // print the results to the Serial Monitor:
  #if defined (__DEBUG_SERIAL__)
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print("\t ");

    Serial.print("output = ");
    Serial.print(outputValue);
  #endif
}

void loop() {
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 500, 0, 255) * shiftValue;
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  tick();

  #if defined (__DEBUG_SERIAL__)
    // End of Line for Serial Out
    Serial.println();
  #endif

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(sleep);
}
