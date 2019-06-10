#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "PIRMotionSensor.h"

#define LOGO "ON"

/*

https://www.instructables.com/id/Tutorial-to-Interface-OLED-091inch-128x32-With-Ard/

*/

// Display Controller: SSD1306 von DSDTech.
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

// PIR Motion Sensor Helper Class
PIRMotionSensor_C pir(PIN4);

void setup(void) {
   Serial.begin(9600);
   pir.setup();

   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, LOW);

   u8g2.begin();

#ifdef LOGO
   u8g2.clearBuffer();					// clear the internal memory
   u8g2.setFont(u8g2_font_logisoso18_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(8,29,"XD23FE39");	// write something to the internal memory
   u8g2.sendBuffer();					// transfer internal memory to the display
   delay(3000);

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso18_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(4,29,"v.19.6.10");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(2000);

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso18_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(4,26,"PIR");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(2000);

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso18_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(4,26,"ready!");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(2000);
#endif
}

char pir_display[25];

void loop(void) {

  switch ( pir.detect() ) {
    case 2: // Motion
      u8g2.clearBuffer();         // clear the internal memory
      u8g2.setFont(u8g2_font_logisoso18_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
      u8g2.drawStr(4,26,"MOTION!");  // write something to the internal memory
      u8g2.sendBuffer();         // transfer internal memory to the display
      delay(2000);
      break;
    case 1: // Unlock
      sprintf(pir_display, "T: %ld ms", (unsigned long) pir.getLockTimer());
      u8g2.clearBuffer();         // clear the internal memory
      u8g2.setFont(u8g2_font_7x14_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
      u8g2.drawStr(6,16,"UNLOCK");  // write something to the internal memory
      u8g2.drawStr(6,30,pir_display);  // write something to the internal memory
      u8g2.sendBuffer();         // transfer internal memory to the display
      delay(4000);
      digitalWrite(LED_BUILTIN, LOW);
      break;
    default: // Nothing changed
      sprintf(pir_display, "Alerts: %d", pir.getAlerts());
      u8g2.clearBuffer();         // clear the internal memory
      u8g2.setFont(u8g2_font_logisoso16_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
      u8g2.drawStr(6,26,pir_display);  // write something to the internal memory
      u8g2.sendBuffer();         // transfer internal memory to the display
      break;
  }

   delay(100);

}
