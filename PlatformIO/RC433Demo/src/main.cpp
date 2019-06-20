#include <Arduino.h>
#include "RCSwitch.h"
#include "RC433Telegram.h"
#include "RC433Monitor.h"

RC433Monitor* rc433 = new RC433Monitor(PIN2);

void setup() 
{
  // Serial Monitor aktivieren
  Serial.begin(9600);
  
  // RC433 Modul initialisieren 
  rc433->init();
}

void loop() 
{
  // RC433 auslesen und Daten anzeigen
  if (rc433->dump()) {
    // Kurze Wartezeit nach Empfang der Daten
    delay(200);
  }

  // Wartezeit bis zur nächsten Abfrage von RC433
  delay(200);
}