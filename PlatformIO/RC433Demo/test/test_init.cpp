#include <Arduino.h>
#include "RCSwitch.h"
#include "RC433Telegram.h"
#include "RC433Monitor.h"

// Default: interrupt 0 => PIN2
// https://www.arduino.cc/reference/de/language/functions/external-interrupts/attachinterrupt/
// See also: digitalPinToInterrupt(PIN2)


RC433Monitor rc433 = RC433Monitor(PIN2);

void main() 
{
  // RC433 Modul initialisieren 
  rc433.init();

}
