
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#include "PIRMotionSensor.h"
#include "OLEDText.h"

extern U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2;

void relais_switch(uint8_t pin, int level);
void relais_init(uint8_t pin, bool low_level_trigger);

/*

https://www.instructables.com/id/Tutorial-to-Interface-OLED-091inch-128x32-With-Ard/

*/

// PIR Motion Sensor Helper Class
PIRMotionSensor_C pir(PIN4);

unsigned long pc_display = 0;

void setup(void) {

  // Initialisierung
  Serial.begin(9600);    // Serial Monitor
  pir.setup();           // PIR
  oled_setup();          // OLED Display (I2C Schnittstelle)
  relais_init(5, true);

  while (pir.locked()) {
    // Eingebaute LED soll blinken, solange PIR gelockt ist
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }

}

char pir_display[25];

void loop(void) {

  switch ( pir.detect() ) {
    case 2: // Motion
      pc_display = 0;
      u8g2.clearBuffer();         // clear the internal memory
      u8g2.setFont(u8g2_font_logisoso18_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
      u8g2.drawStr(4,26,"MOTION!");  // write something to the internal memory
      u8g2.sendBuffer();         // transfer internal memory to the display
      relais_switch(5, LOW);
      delay(2000);
      break;
    case 1: // Unlock
      pc_display = 0;
      sprintf(pir_display, "T: %ld ms", (unsigned long) pir.getLockTimer());
      u8g2.clearBuffer();         // clear the internal memory
      u8g2.setFont(u8g2_font_7x14_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
      u8g2.drawStr(4,16,"UNLOCK");  // write something to the internal memory
      u8g2.drawStr(4,30,pir_display);  // write something to the internal memory
      u8g2.sendBuffer();         // transfer internal memory to the display
      delay(4000);
      relais_switch(5, HIGH);
      u8g2.clearBuffer();         // clear the internal memory
      u8g2.sendBuffer();         // transfer internal memory to the display      
      break;
    default: // Nothing changed
      if (pir.locked() && pc_display != 2) { 
        pc_display = 2;
        sprintf(pir_display, "Alerts: %d", pir.getAlerts());
        u8g2.clearBuffer();         // clear the internal memory
        u8g2.setFont(u8g2_font_logisoso16_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
        u8g2.drawStr(4,26,pir_display);  // write something to the internal memory
        u8g2.sendBuffer();         // transfer internal memory to the display
      }
      break;
  }

   delay(10);
}


/**
 * Initialisierung des Relais. Es werden HIGH- und LOW-Level-Trigger
 * Relaismodule unterstützt. 
 */
void relais_init(uint8_t pin, bool low_level_trigger)
{
  // Anschluss-PIN als Ausgang setzen
  pinMode(pin, OUTPUT);
  
  // Low-Level-Trigger Module schalten beim Wechsel nach LOW 
  if (low_level_trigger)
  {
    relais_switch(pin, HIGH);    // AUS
  }
  else
  {
    relais_switch(pin, LOW);     // AUS
  }  
}

/**
 * Schaltet das Relaimodul an PIN pin auf LEVEL level.
 */
void relais_switch(uint8_t pin, int level)  
{
  digitalWrite(pin, level);
}
