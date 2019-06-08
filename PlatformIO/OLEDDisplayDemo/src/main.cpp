#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

#define LOGO "ON"

/*

https://www.instructables.com/id/Tutorial-to-Interface-OLED-091inch-128x32-With-Ard/

*/

// Display Controller: SSD1306
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

unsigned long pc_start = millis();

void setup(void) {
   Serial.begin(9600);

   u8g2.begin();

#ifdef LOGO
   u8g2.clearBuffer();					// clear the internal memory
   u8g2.setFont(u8g2_font_logisoso18_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(8,29,"XD23FE39");	// write something to the internal memory
   u8g2.sendBuffer();					// transfer internal memory to the display
   delay(3000);

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso18_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(4,29,"BUS clock");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(2000);

   char clock[10];
   sprintf(clock, "%10d", (int) u8g2.getBusClock());
   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso16_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(10,29,clock);  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(2000);

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso18_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(4,26,"System");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(1000);

   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso18_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(4,26,"ready!");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(2000);
#endif
}

   void loop(void) {

   // Reserviere 25 Zeichen für die Ausgabe des Timers
   char pc_display[25];

   // Berechne die Timer-Werte aus den vergangenen Millisekunden (alle 60 Sekunden von vorne)
   unsigned long timer =  (unsigned long) (millis() - pc_start) ;

   // Formatiere die Ausgabe und schreibe in Char-Buffer
   sprintf(pc_display, "T: %ld ms", timer);

   // Ausgabe der Timer-Page auf dem Dispplay
   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_6x12_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(34,12,"T I M E R");  // write something to the internal memory
   u8g2.drawHLine(4,15,120);
   // u8g2.setFont(u8g2_font_7x14_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.setFont(u8g2_font_9x15_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(6,32,pc_display);  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(200);
}
