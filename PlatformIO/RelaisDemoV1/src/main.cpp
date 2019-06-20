#include <Arduino.h>

#define PIN_RELAIS_A  8

// Funktion für Signal-LED-Steuerung
void blink(uint8_t pin, byte repeat, int ms = 200);

/*
 
 Relais 5V/230V Raspberry Pi Modul Channel Relay Arduino

 - 5V Relais Modul 1-Kanal
 - 5 Volt 1-Kanal-Relais-Schnittstellenkarte
 - zur Steuerung von Verbrauchern bis 230 Volt
 - Verbrauch 50-60mA.
 - Hochstrom-Relais: AC250V 10A; DC30V 10A.
 - LED zur Statusanzeige welcher Ausgang aktiv ist

  Relais-Module mit Low-Level-Trigger schalten, sobald am Anschluss-PIN
  LOW anliegt. Soll bei der Initialisierung des Moduls KEIN Schaltvorgang
  ausgelöst werden, muss der Anschluss-PIN auf HIGH gesetzt werden.

 */
void relais_init(uint8_t pin, bool low_level_trigger = false);
void relais_switch(uint8_t pin, int level); 

/**
 * Arduino SETUP Procedure.  
 * 
 */ 
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  relais_init(PIN_RELAIS_A, true);     // LLT-Relais initialisieren (AUS => HIGH)
  delay(5000);
  relais_switch(PIN_RELAIS_A, LOW);    // AN bei LLT-Relais
  delay(5000);
  relais_switch(PIN_RELAIS_A, HIGH);   // AUS bei LLT-Relais
}

/**
 * Arduino LOOP Procedure.
 * 
 */
void loop() {
  blink(LED_BUILTIN, 1, 200);
}


/**
 * Lässt eine LED an PIN pin repeat-mal blinken.
 */
void blink(uint8_t pin, byte repeat, int ms = 200) {
  for (byte i = 0; i < repeat; i++)
  {
    digitalWrite(pin, HIGH);
    delay(ms);
    digitalWrite(pin, LOW);
    delay(ms);  
  }
}

/**
 * Initialisierung des Relais. Es werden HIGH- und LOW-Level-Trigger
 * Relaismodule unterstützt. 
 */
void relais_init(uint8_t pin, bool low_level_trigger)
{
  // Anschluss-PIN als Ausgang setzen
  pinMode(PIN_RELAIS_A, OUTPUT);
  
  // Low-Level-Trigger Module schalten beim Wechsel nach LOW 
  if (low_level_trigger)
  {
    relais_switch(PIN_RELAIS_A, HIGH);    // AUS
  }
  else
  {
    relais_switch(PIN_RELAIS_A, LOW);     // AUS
  }  
}

/**
 * Schaltet das Relaimodul an PIN pin auf LEVEL level.
 */
void relais_switch(uint8_t pin, int level)  
{
  digitalWrite(pin, level);
}
