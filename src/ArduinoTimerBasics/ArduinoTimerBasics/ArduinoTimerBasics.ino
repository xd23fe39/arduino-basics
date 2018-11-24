/*
  Beleuchtung für Weihnachtsdorf 3V/0.6W (10 LEDs * 0.06W)
  
  Basiert auf dem VBeispiel:

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
  https://www.arduino.cc/reference/en/
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 300;        // value between 0 (0V) and 500 (5V)
int outputValue = 0;          // calculate it 0..255
float shiftValue = 1.09;       // shift output 1.1 = +10%

int  sleep = 20;
unsigned long ticker = 0;
unsigned long t_lap = 0;
unsigned long t_now = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void tick() {
  Serial.print("ticker = ");
  Serial.print(ticker);
  Serial.print("\t ");
  t_lap = t_now;
  t_now = millis();
  Serial.print("t_lap = ");
  Serial.print(t_lap);
  Serial.print("\t ");  
  Serial.print("t_now = ");
  Serial.print(t_now);
  Serial.print("\t ");  
  Serial.print(int(t_lap / 60000));
  Serial.print(" min ");
  Serial.print(int(t_lap / 1000));
  Serial.print(" sec ");
  Serial.print(int(t_lap % 1000));
  Serial.print(" milli.");
  Serial.print("\t ");
  ticker += 1;
}

void loop() {
  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 500, 0, 255) * shiftValue;
  // change the analog out value:
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t ");

  tick();
  
  Serial.print("output = ");
  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(sleep);
}
