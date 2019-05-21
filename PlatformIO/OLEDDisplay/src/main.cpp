 #include <Arduino.h>

/*
 * U8glib by oliver
 * 1.19.1
 * A library for monochrome TFTs and OLEDs
 */
 #include "U8glib.h"

U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE); // Just for 0.91”(128*32)
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);// for 0.96” and 1.3”

void printOLED(char* text, int y = 10) {
  u8g.firstPage();  
  do { 
    u8g.drawStr(0, y, text);
  } while (u8g.nextPage());
}

void setup(void) {
  // flip screen, if required
  // u8g.setRot180();
  u8g.setFont(u8g_font_7x13);
}

char str[32];

void loop(void) {
  sprintf(str, "Device: %s", "Arduino");
  printOLED(str);
  delay(2000);
  sprintf(str, "Arduino: %s", __VERSION__);
  printOLED(str);
  delay(2000);
}
