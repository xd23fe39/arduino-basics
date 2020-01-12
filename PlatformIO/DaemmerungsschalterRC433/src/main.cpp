#include <Arduino.h>
#include <RCSwitch.h>

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
  int alive = 20;
};

struct BusinessLogic {
  int alerts = 0;
  int sensibility = 48;
  int delay = 1000;
  int mode = 0;
  unsigned long timer;
  unsigned long on_time = 60*10;
  unsigned long off_time = 60*1;
};

PhotoTester test;
SignalLED led;
BusinessLogic blogic;
RCSwitch rcsend = RCSwitch();

// Funktionsdefinitionen
int read();
int logic();
void blink(int n);
void alive(int n);
void sendRC433(bool on);
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
  // RCSwitch
  pinMode(10,OUTPUT);
  rcsend.enableTransmit(10);
  rcsend.setProtocol(1);
  rcsend.setPulseLength(362);
  rcsend.setRepeatTransmit(5);  // Initialisiere Datenstruktur
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
  if (blogic.mode == 0 && test.level < blogic.sensibility) {
    blink(3);
    sendRC433(true);
    blogic.alerts++;
    blogic.mode = 1;
    blogic.timer = blogic.on_time;
  }
  else if (blogic.mode == 1 && blogic.timer < 1) {
    blink(5);
    sendRC433(false);
    blogic.mode = 2;
    blogic.timer = blogic.off_time;
  }
  else if (blogic.mode == 2 && blogic.timer >= 1) {
    alive(1);
  }
  else if (blogic.mode == 1 && blogic.timer < 1) {
    blogic.mode = 2;
  }
  else if (blogic.mode == 2 && blogic.timer < 1) {
    blogic.mode = 0;
  }
  delay(blogic.delay);
  if (blogic.timer > 0)
    blogic.timer--;
  return blogic.mode;
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
  Serial.print(" timer ");
  Serial.print(blogic.timer);
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

void alive(int n) {
  for (int i = 0; i < n; i++)
  {
    digitalWrite(led.pin, HIGH);
    delay(led.alive);
    digitalWrite(led.pin, LOW);
    delay(led.alive);
  }
}

void sendRC433(bool on) {
  if (on)
  {
    rcsend.send("010100000100010101010001");     // A_ON
    rcsend.send("010100000101000101010001");     // B_ON
  }
  else 
  {
    rcsend.send("010100000100010101010100");     // A_OFF
    rcsend.send("010100000101000101010100");     // B_OFF
  }
}