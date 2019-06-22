#include <Arduino.h>

struct PhotoTester {
  uint8_t pin = A0;
  int pmin = 48;
  int value;
  int level;
  char daynight;
};

PhotoTester test;

int read();

void setup() {
  // Serial Monitor initialisieren
  Serial.begin(9600);
  // Initialisiere Datenstruktur
  test.value = analogRead(test.pin);
}

void loop() {
  // Einlesen der Sensorwerte
  read();
  // Ausgabe der Sensorwerte
  Serial.print("Photo: Value ");
  Serial.print(test.value);
  Serial.print(" Level ");
  Serial.print(test.level);
  Serial.print(" DayNight ");
  Serial.print(test.daynight);
  Serial.println();
  // Warte 2 Sekunden
  delay(2000);
}

/**
 * Auslesen der Sensoren
 */
int read() {
  test.value = analogRead(test.pin);        // Fototransistor
  test.level = map(test.value, 0, 1023, 0, 100);
  test.daynight = (test.level < test.pmin ? 'N' : 'D');
  return test.value;
}
