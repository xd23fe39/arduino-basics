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

struct SignalLED {
  uint8_t pin = 7;
  int level = LOW;
  int delay = 200;
};

struct BusinessLogic {
  int alerts = 0;
  int sensibility = 8;
};

PhotoTester test;
SignalLED led;
BusinessLogic blogic;

// Funktionsdefinitionen
int read();
int logic();
void blink(int n);
void dump();

/**
 * Arduino setup-Methode
 */
void setup() {
  // Serial Monitor initialisieren
  Serial.begin(9600);
  Serial.println(test.name);
  // LED
  pinMode(led.pin, OUTPUT);
  digitalWrite(led.pin, led.level);
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
  // Verarbeitung der Werte (Logik)
  logic();
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

int logic() {
  if (abs(test.delta) > blogic.sensibility) {
    blogic.alerts++;
    blink(3);
  }
}

/**
 * Serial Dump 
 */
void dump() {
  Serial.print("Photo: Messung ");
  Serial.print(test.count);
  Serial.print(" Value ");
  Serial.print(test.value);
  Serial.print(" Delta ");
  Serial.print(test.delta);
  Serial.print(" Level ");
  Serial.print(test.level);
  Serial.print(" BL.alerts ");
  Serial.print(blogic.alerts);
  Serial.print(" DayNight ");
  Serial.print(test.daynight);
  Serial.println();
}

void blink(int n) {
  for (int i = 0; i < n; i++)
  {
    digitalWrite(led.pin, HIGH);
    delay(led.delay);
    digitalWrite(led.pin, LOW);
    delay(led.delay);
  }
}