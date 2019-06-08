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
   long counter;
};

PIRSensor_T pir1;

 void setup(void) {
   Serial.begin(9600);

   pinMode(LED_BUILTIN, OUTPUT);
   digitalWrite(LED_BUILTIN, LOW);

   pinMode(PIN4, INPUT);
   pir1.timer = millis() - pc_start;
   pir1.value = digitalRead(PIN4);
   pir1.counter = 0;

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

   u8g2.clearBuffer();					// clear the internal memory
   u8g2.setFont(u8g2_font_logisoso16_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawHLine(14,2,100);
   u8g2.drawStr(14,26,"Scanning...");  // write something to the internal memory
   u8g2.sendBuffer();					// transfer internal memory to the display
   delay(1000);

   pir1.timer = millis() - pc_start;
   
   int pir_in = digitalRead(PIN4);
   if (pir_in == HIGH && pir1.value == LOW) {
      digitalWrite(LED_BUILTIN, HIGH);
      pir1.counter++;

      char pc_display[12];
      sprintf(pc_display, "T: %ld ms", (unsigned long) millis() - pc_start);
      u8g2.clearBuffer();         // clear the internal memory
      u8g2.setFont(u8g2_font_7x14_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
      u8g2.drawStr(6,16,"Detected!");  // write something to the internal memory
      u8g2.drawStr(6,30,pc_display);  // write something to the internal memory
      u8g2.sendBuffer();         // transfer internal memory to the display
      delay(2000);
      digitalWrite(LED_BUILTIN, LOW);
   }
   pir1.value = pir_in;
   char pir_display[12];
   sprintf(pir_display, "PIR: %ld (%d)", pir1.counter, pir_in);
   u8g2.clearBuffer();         // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso16_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(6,26,pir_display);  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
   delay(2000);
   
   double vcc_value = map(analogRead(PIN_A2), 0, 1023, 0, 5);
   String vcc_str = ((vcc_value >=0) ? "+" : "-") + String(vcc_value) + " V";
   char vcc_buf[10];
   vcc_str.toCharArray(vcc_buf, 10);
   u8g2.clearBuffer();					// clear the internal memory
   u8g2.setFont(u8g2_font_logisoso24_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(18,30,vcc_buf);	// write something to the internal memory
   u8g2.sendBuffer();					// transfer internal memory to the display
   delay(500);

   // Alive   
   digitalWrite(LED_BUILTIN, HIGH);
   delay(20);
   digitalWrite(LED_BUILTIN, LOW);
   delay(20);
}
