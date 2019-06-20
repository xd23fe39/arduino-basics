#include <RCSwitch.h>
#include "RC433Telegram.h"
#include "RC433Monitor.h"
#include "output.h"

void RC433Monitor::dump_init() 
{
  Serial.print("\nRC433Demo Application Receiver Modul Tester\n\n");
  Serial.print("PIN DATA: ");
  Serial.print(PIN_DATA);
  Serial.print(" Interrupt: ");
  Serial.print(INT_DATA);
  Serial.println();
}

void RC433Monitor::dump_telegram() 
{
  Serial.print("Telegram - ");

  // https://github.com/sui77/rc-switch/
  output(data.value, data.bitlength, data.delay, data.rawdata, data.protocol);
}

void RC433Monitor::warning() 
{
  Serial.println("WARNING: Initialization error!");
  while (true) 
  {
    digitalWrite(PIN_LED, HIGH);
    delay(200);
    digitalWrite(PIN_LED, LOW);
    delay(200);
  }
}

// Default: interrupt 0 => PIN2
// https://www.arduino.cc/reference/de/language/functions/external-interrupts/attachinterrupt/
// See also: digitalPinToInterrupt(PIN2)

RC433Monitor::RC433Monitor(uint8_t pin_data) 
{
  // Ermitteln der Interruptnummer
  INT_DATA = digitalPinToInterrupt(pin_data);
  // Falls kein Interrupt-PIN
  if (INT_DATA == NOT_AN_INTERRUPT || INT_DATA == 255)  { 
    warning();  
    exit(-1);
  }
  // Initialisierung
  PIN_DATA = pin_data;
  // Objekt während der Laufzeit erzeugen
  rcmodul = new RCSwitch();
}

RC433Monitor::~RC433Monitor() 
{
  // Funktion beenden
  rcmodul->disableReceive(); 

  // dynam. Speicher freigeben
  delete(rcmodul);
}

void RC433Monitor::init() {
  rcmodul->enableReceive(INT_DATA);
  dump_init();
}

bool RC433Monitor::dump() {
  if (receive()) {
    dump_telegram();
  }
}


bool RC433Monitor::receive() {
  if (rcmodul->available()) {
    data.value = rcmodul->getReceivedValue();
    data.protocol = rcmodul->getReceivedProtocol();
    data.bitlength = rcmodul->getReceivedBitlength();
    data.delay = rcmodul->getReceivedDelay();
    data.rawdata = rcmodul->getReceivedRawdata();
    rcmodul->resetAvailable();
    delay(20);
    return true;
  }
  return false;
}

