#ifndef _RC433TELEGRAM_H_
#define _RC433TELEGRAM_H_

struct RC433Telegram {
  unsigned long value;
  unsigned long protocol;
  unsigned int bitlength;
  unsigned int delay;
  unsigned int* rawdata;
};

#endif