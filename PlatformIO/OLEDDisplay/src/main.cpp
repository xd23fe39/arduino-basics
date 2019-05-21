 #include <Arduino.h>

/*
 * U8glib by oliver
 * 1.19.1
 * A library for monochrome TFTs and OLEDs
 */
 #include "U8glib.h"

U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE); // Just for 0.91”(128*32)
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);// for 0.96” and 1.3”


int sindex = 0;

void draw(String text, unsigned y = 10, unsigned x = 0) {
  u8g.setPrintPos(x, y); 
  u8g.print(text);
}

void pictureLoop(String t1, String t2) {
  u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_8x13B);
    draw(t1, 12);
    // u8g.setFont(u8g_font_unifont);
    u8g.setFont(u8g_font_7x13);
    draw(t2, 30);
  } while( u8g.nextPage() );  
}

void setup(void) {
  // flip screen, if required
  // u8g.setRot180();
  

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}

void loop(void) {
  pictureLoop("OLED Display", "SCL SDA VCC gND");
  delay(1000);
}
