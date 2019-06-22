#include <Arduino.h>

struct PhotoTester {
  String name = "Fotowiderstand an 3kOhm Arbeitswiderstand";
  uint8_t pin = A0;
  int pmin = 48;
  int value;
  int delta = 0;
  int level = 0;
  char daynight = '-';
  unsigned long count = 0;
};

PhotoTester test;

// Funktionsdefinitionen
int read();
void dump();

/**
 * Arduino setup-Methode
 */
void setup() {
  // Serial Monitor initialisieren
  Serial.begin(9600);
  Serial.println(test.name);
  // Initialisiere Datenstruktur
  test.value = analogRead(test.pin);
}

/**
 * Arduino loop-Methode
 */
void loop() {
  // Einlesen der Sensorwerte
  read();
  // Ausgabe der Sensorwerte
  dump();
  // Warte 2 Sekunden
  delay(2000);
}

/**
 * Auslesen der Sensoren
 */
int read() {
  int in = analogRead(test.pin);        // Fototransistor
  test.delta = in - test.value;
  test.value = in;
  test.level = map(test.value, 0, 1023, 0, 100);
  test.daynight = (test.level < test.pmin ? 'N' : 'D');
  test.count++;
  return test.value;
}

/**
 * Serial Dump 
 */
void dump() {
  char buffer[10];
  Serial.print("Photo: Messung ");
  Serial.print(test.count);
  Serial.print(" Value ");
  Serial.print(test.value);
  Serial.print(" Delta ");
  Serial.print(test.delta);
  Serial.print(" Level ");
  Serial.print(test.level);
  Serial.print(" DayNight ");
  Serial.print(test.daynight);
  Serial.println();
}
