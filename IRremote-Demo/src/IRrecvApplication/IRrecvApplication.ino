/*
 * IR-Fernbedienung Universal Empfänger mit 38kHz 
 *
 * Required:
 * http://z3t0.github.io/Arduino-IRremote/
 * https://github.com/z3t0/Arduino-IRremote
 * 
 * Tested on: Arduino Nano Clone ATmega 328P v3 
 *
 * Universal IR Infrarot Remote Receiver:
 *   Modell: CHQ1838
 *   Betriebsspannung: 2.7-5.5V
 *   Empfangsbereich: 15-18M
 *   Führen Pin Pitch: 2.53mm
 *   Leistung: 180 mW 
 *
 */

#include <IRremote.h>

/* 
 *  Default is Arduino pin D11. 
 *  You can change this to another available Arduino Pin.
 *  Your IR receiver should be connected to the pin defined here
 */
#define PIN_IR_RECEIVER  11

#define KEY_PAD_001 0x6D92807F // Kenwood IR Remote Control Key 1

#define null 0x0

// ===================================================================
// Component Class: IRReceiver
// =================================================================== 

class IRReceiver {
private:
  char* name = "IR-Receiver Application";
  char* version = "16.6.002";
  IRrecv* irrecv = null;
  unsigned long ir_code = 0;
  unsigned long ir_type = 0;
  decode_results ir_receive;
public:

  void setup(int pin) {
    Serial.begin(9600);
    Serial.print("Application: ");
    Serial.println(name);
    Serial.print("Version: ");
    Serial.println(version);
    Serial.println("Serial Monitoring is started.");
    Serial.println("Entering setup()-Function.");
    Serial.print("Preprocessing at: ");
    Serial.println(__DATE__);  
  
    irrecv = new IRrecv(pin);
  
    // IR Receiver initialisieren
    this->irrecv->enableIRIn(); // Start the receiver
  }

  void loop() {
    if (this->irrecv->decode(&ir_receive)) {
      Serial.print("IR Receiver: ");
      ir_code = ir_receive.value;
      ir_type = ir_receive.decode_type;
      Serial.print(ir_receive.value);    
      Serial.print(" | ");
      Serial.print(ir_receive.value, HEX);
      Serial.print(" | ");
      Serial.println(ir_type);
      // dump(&results);
      this->receive(ir_code);
      Serial.println("Waiting 50ms before resume IR receiver!");    
      delay(50);
      this->irrecv->resume(); // Receive the next value
    }
   }
   
   virtual void receive(unsigned long code) {
      switch (code) {
      default:
        Serial.println(" * Virtual method receive(...) is not implemented, yet [WARNING]");    
        break; 
      }
   }
   
}; // END-of-class

class IRKennwood : public IRReceiver {
public:
   virtual void receive(unsigned long code) {
      switch (code) {
      case KEY_PAD_001:
        Serial.println(" * Pushed KEY is 001 on your remote control!");    
        break;
      default:
        Serial.println(" * Received unknown signal from your remote control [WARNING]");    
        break; 
      }
   }
};

// ===================================================================
// Arduino Main Functions
// =================================================================== 

IRKennwood ir;

/**
 * Initialisierung 
 */
void setup()
{
  pinMode(9, OUTPUT);     
  pinMode(10, OUTPUT);     
  digitalWrite(9, HIGH);   
  digitalWrite(10, LOW);   

  // PIN 11 ist der SIGNAL-PIN
  ir.setup(PIN_IR_RECEIVER);
}

// ===================================================================
// LOOP 
// =================================================================== 

/**
 * Hauptprogramm
 */
void loop() {
  ir.loop();
  delay(1);
}

