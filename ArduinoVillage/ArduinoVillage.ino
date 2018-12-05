/*
  Beleuchtung für Weihnachtsdorf 3V/0.6W (10 LEDs * 0.06W)
  
  Basiert auf dem VBeispiel:

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 300;        // value between 0 (0V) and 500 (5V)
int outputValue = 0;          // calculate it 0..255

int sleep = 20;

struct timer {
  unsigned long value;
  unsigned long lap;
  unsigned long now;  
  unsigned long rotate;  
  int sleep;
  int rt_hour;
  int rt_min;
  int rt_sec;
  int rt_milli;
};

/*
 * PWM Pins: 3, 5, 6, 9, 10, and 11.
 */
struct ledSet {
  unsigned PIN;
  int spannung;
  int value;
  int fade;
  unsigned long tick;
  bool on;
  int low;
};

timer worldtime = {0, 0, 0, 20, 0, 0, 0};
ledSet laterne = {9, 300, 0, 2, 0, false, 100};
ledSet dorf = {10, 300, 0, 2, 0, false, 25};

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

unsigned long tick(timer &t) {
  t.lap = t.now;
  t.now = millis();
  t.rt_hour = int((t.lap / (60000 * 60))%24);
  t.rt_min = int((t.lap / 60000) % 60);
  t.rt_sec = int((t.lap / 1000 ) % 60);
  t.rt_milli = int(t.lap % 1000);
  t.rotate = int(t.lap / 1000 );
  t.value += 1;
  Serial.print("value = ");
  Serial.print(t.value);
  Serial.print("\t ");
  Serial.print("lap = ");
  Serial.print(t.lap);
  Serial.print("\t ");  
  Serial.print("now = ");
  Serial.print(t.now);
  Serial.print("\t ");  
  Serial.print(t.rt_hour);
  Serial.print(" h ");
  Serial.print(t.rt_min);
  Serial.print(" min ");
  Serial.print(t.rt_sec);
  Serial.print(" sec ");
  Serial.print(t.rt_milli);
  Serial.print(" milli.");
  Serial.print("\t ");
  return t.value;
}

int updateLED(ledSet &led) {
  analogWrite(led.PIN, map(led.value, 0, 500, 0, 255));
  return led.value;
}

int flackern(ledSet &led, int min, int max) {
  // map it to the range of the analog out:
  led.value = led.spannung - random(min, max); 
  led.tick++;
  return updateLED(led);
}


int fadein(ledSet &led) {
  led.tick++;
  if (led.value + led.fade >= led.spannung ) {
    led.value = led.spannung;
    led.on = true;
  }
  else
    led.value += led.fade;
  return updateLED(led);;
}

int fadeout(ledSet &led) {
  led.tick++;
  if (led.value - led.fade <= led.low ) {
    led.value = led.low;
    led.on = false;
  }
  else
    led.value -= led.fade;
  return updateLED(led);;
}


void loop() {

  // timer
  tick(worldtime);

  // Laterne anschalten und flackern
  if ( laterne.on )
    flackern(laterne, 0, 120);
  else
    fadein(laterne);

  // Dorf beleuchten  
  if (worldtime.rotate > 15)
    fadeout(dorf);
  else
    fadein(dorf);  

  // Debug Dorf LED Value
  Serial.print("led = ");
  Serial.print(dorf.value);
  Serial.print("\t ");

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t ");
  
  Serial.print("output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(sleep);
}