#include <Arduino.h>

#include <IRremote.h>

#define PIN_IR 3
#define PIN_DETECT 11
#define PIN_STATUS 6

IRsend irsend;
int in = 0;

void setup()
{
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);  

  Serial.begin(9600);
  pinMode(PIN_DETECT, INPUT);
  pinMode(PIN_STATUS, OUTPUT);
  irsend.enableIROut(38);
  irsend.mark(0);
}

void loop() {
  in = analogRead(PIN_DETECT);
  digitalWrite(PIN_STATUS, (in > 320));
  Serial.print("Read: ");
  Serial.println(in);
  delay(100);
}