/*
 *
 * 
 * https://funduino.de/nr-03-433mhz-funkverbindung
 * 
 */

#include <Arduino.h>
#include <RCSwitch.h>
#include <SignalLED.h>
#include <output.h>

// #define DEBUG

struct AnalogSensor {
  uint8_t pin;
  int value;
  int value_b;
  int tolerance;
  int delta;
};

class RCModul {

protected:

  RCSwitch rcmonitor = RCSwitch();
  RCSwitch rcsender = RCSwitch();
  SignalLED signalLED = SignalLED(PIN4);
  AnalogSensor sensor;

  unsigned long rcvalue;
  unsigned int rcbitlen;
  unsigned int rcdelay;
  unsigned int rcprot;
  unsigned int* rcrawdata;

  unsigned long rc_timer = 0;

  long data_send[2] = {5263700, 5263697};

public:

  static const int RECEIVER_INT = 0;         // Default: interrupt 0 => PIN2
  static const int TRANSMITTER_PIN = 10;     // Default: PIN for Transmitter Data
  static const int TRANSMITTER_VCC = PIN7;   // Default: Transmitter Standby and VCC
  static const int SENSOR_PIN = PIN_A0;      // Default: Analog sensor

  void setupTransmitter(uint8_t pin) {
    pinMode(TRANSMITTER_VCC, OUTPUT); 
    rcsender.enableTransmit(pin);
    rcsender.setProtocol(1);
    rcsender.setPulseLength(362);
    rcsender.setRepeatTransmit(5);
    Serial.print("  Transmitter PIN: ");
    Serial.println(pin);
  }

  void setupReceiver(int interrupt) {
    rcmonitor.enableReceive(interrupt);  
    Serial.print("  Receiver interrupt: ");
    Serial.println(interrupt);
  }

  void setupSensor(uint8_t pin_sensor, int tolerance = 2) {
    sensor.pin = pin_sensor;
    sensor.value = analogRead(pin_sensor);
    sensor.value_b = sensor.value;
    sensor.tolerance = tolerance;
    Serial.print("  Sensor analog PIN: ");
    Serial.println(pin_sensor);
  }

  void setupSerial(unsigned long baud = 9600) {
    Serial.begin(baud);
    Serial.println("\nRCModul 433MHz using rcmonitor\n");
  }

  void setupAll() {
    setupSerial();
    setupSensor(SENSOR_PIN);
    setupTransmitter(TRANSMITTER_PIN);
    setupReceiver(RECEIVER_INT);
    signalLED.start();
  }

  void wakeupTransmitter(uint8_t PIN_VCC, uint8_t PIN_DATA) {
    Serial.println("  Transmitter wakeup!");  
    digitalWrite(PIN_VCC, HIGH);    
    rcsender.enableTransmit(PIN_DATA);
    rcsender.setProtocol(1);
    rcsender.setPulseLength(362);
    rcsender.setRepeatTransmit(5);
  }

  void standbyTransmitter(uint8_t PIN_VCC) {
    delayMicroseconds(100);
    digitalWrite(PIN_VCC, LOW); 
    Serial.println("  Transmitter standby!");  
  }

  void alive() {
    signalLED.alive(1, 20);
  }

  int readSensor() {
    sensor.value = analogRead(SENSOR_PIN);
    return sensor.value;
  }

  bool releaseSensor() {
    int delta = sensor.value - sensor.value_b;
    if (abs(delta) > sensor.tolerance) { 
      sensor.value_b = sensor.value;
      sensor.delta = delta;
      Serial.println("\n----");
      Serial.print("  Sensor: Value ");
      Serial.print(sensor.value);
      Serial.print(", Delta ");
      Serial.print(sensor.delta);
      Serial.print(", Timer ");
      Serial.println(rc_timer);
      return true;
    }
    return false;
  }

  int getSensorValue() {
    return sensor.value;
  }

  void sendData(const char* data) {
    Serial.println("----");
    wakeupTransmitter(TRANSMITTER_VCC, TRANSMITTER_PIN);
    rcsender.send(data);
    Serial.print("  Transmitter send data: ");
    Serial.println(data);
    standbyTransmitter(TRANSMITTER_VCC);
  }

  void sendDemo() {
    rcsender.send("010100000101000101010001");
    delay(5000);
    rcsender.send("010100000101000101010100");
    delay(10000);
  }



  void monitor() {
    if (rcmonitor.available()) {
      rcvalue = rcmonitor.getReceivedValue();
      rcbitlen = rcmonitor.getReceivedBitlength();
      rcdelay = rcmonitor.getReceivedDelay();
      rcrawdata = rcmonitor.getReceivedRawdata();
      rcprot = rcmonitor.getReceivedProtocol();
      Serial.println("----");
      Serial.print("  Receiver: Value ");
      Serial.print(rcvalue);
      Serial.print(", Binary ");
      Serial.println(*rcrawdata, BIN);
#ifdef DEBUG_DETAILS
      output(rcvalue, rcbitlen, rcdelay, rcrawdata,rcprot);
#endif
      rcmonitor.resetAvailable();
    }
  }

  unsigned long loop() {
    return rc_timer++;
  }

  boolean wait(long ticks) {
    boolean res = !(rc_timer % ticks);
    #ifdef DEBUG
    if (res) {
      Serial.print("  Debug Timer: ");
      Serial.println(rc_timer);
    }
    #endif
    return res;
  }

  void debug() {
    Serial.print(digitalRead(PIN2));
    Serial.print(",");
  }

};

RCModul rcmodul;

void setup() {
  rcmodul.setupAll();
}

void loop() {  
  rcmodul.loop();
  rcmodul.readSensor();
  if (rcmodul.wait(10000) && rcmodul.releaseSensor()) {
    if (rcmodul.getSensorValue() < 512) 
      rcmodul.sendData("010100000101000101010100");
    else      
      rcmodul.sendData("010100000101000101010001");
    rcmodul.alive();
  }
  rcmodul.monitor();
}

/*
  Example for receiving
  
  https://github.com/sui77/rc-switch/
  
  If you want to visualize a telegram copy the raw data and 
  paste it into http://test.sui.li/oszi/
*/
