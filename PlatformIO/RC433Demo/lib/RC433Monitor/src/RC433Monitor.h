#ifndef _RC433_MONITOR_H_
#define _RC433_MONITOR_H_

class RC433Monitor {

protected:

  RCSwitch* rcmodul;

  uint8_t PIN_DATA;
  uint8_t INT_DATA;

  uint8_t PIN_LED = LED_BUILTIN;

  void dump_init(); 

  void dump_telegram();

  void warning();

public:

  RC433Telegram data;

  RC433Monitor(uint8_t pin_data);

  ~RC433Monitor(); 

  void init();

  bool dump();

  bool receive();

};

#endif