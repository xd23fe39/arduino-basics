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

// Sample usage 
unsigned long pc_start = millis();

struct PIRSensor_T {
   unsigned long timer;
   int value;
};

PIRSensor_T pir1;

 void setup(void) {
   Serial.begin(9600);

   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, LOW);

   pinMode(PIN4, INPUT);
   pir1.timer = millis() - pc_start;
   pir1.value = digitalRead(PIN4);

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
   sprintf(clock, "%.10d", (int) u8g2.getBusClock());
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

   digitalWrite(LED_BUILTIN, HIGH);
   u8g2.clearBuffer();					// clear the internal memory
   u8g2.drawHLine(14,18,100);
   u8g2.sendBuffer();					// transfer internal memory to the display
   delay(1000);
   digitalWrite(LED_BUILTIN, LOW);

   pir1.timer = millis() - pc_start;
   pir1.value = digitalRead(PIN4);
   char pir_display[12];
   sprintf(pir_display, "%d PIR", pir1.value);
   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso16_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(10,26,pir_display);  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(2000);

   char pc_display[12];
   sprintf(pc_display, "%ld ms", (unsigned long) millis() - pc_start);
   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso16_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(10,26,pc_display);  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(2000);
   
   double vcc_value = 3.3;
   String vcc_str = ((vcc_value >=0) ? "+" : "-") + String(vcc_value) + " V";
   char vcc_buf[10];
   vcc_str.toCharArray(vcc_buf, 10);
   u8g2.clearBuffer();					// clear the internal memory
   u8g2.setFont(u8g2_font_logisoso24_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(18,30,vcc_buf);	// write something to the internal memory
   u8g2.sendBuffer();					// transfer internal memory to the display
   delay(2000);
   
}
