#include <Arduino.h>
#include <RCSwitch.h>
#include <output.h>

class Funksteckdose {

protected:

  RCSwitch rcswitch = RCSwitch();
  unsigned long rcvalue;
  unsigned int rcbitlen;
  unsigned int rcdelay;
  unsigned int rcprot;
  unsigned int* rcrawdata;

public:

  void init() {
    Serial.begin(9600);
    rcswitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  }

  void monitor() {
    if (rcswitch.available()) {
      rcvalue = rcswitch.getReceivedValue();
      rcbitlen = rcswitch.getReceivedBitlength();
      rcdelay = rcswitch.getReceivedDelay();
      rcrawdata = rcswitch.getReceivedRawdata();
      rcprot = rcswitch.getReceivedProtocol();
      Serial.print("Received Value: ");
      Serial.println(rcvalue);
      Serial.print("Received Bit length: ");
      Serial.println(rcbitlen);
      Serial.print("Received Protocol: ");
      Serial.println(rcprot);
      Serial.print("Received Delay: ");
      Serial.println(rcdelay);
      Serial.print("Received RAW Data: ");
      Serial.println(*rcrawdata, BIN);
      output(rcvalue, rcbitlen, rcdelay, rcrawdata,rcprot);
      rcswitch.resetAvailable();
    }
  }
};

Funksteckdose funk;

void setup() {
  funk.init();
}

void loop() {
  funk.monitor();
}

/*
  Example for receiving
  
  https://github.com/sui77/rc-switch/
  
  If you want to visualize a telegram copy the raw data and 
  paste it into http://test.sui.li/oszi/
*/
