/* 
 * LED and Button Sample sketch.
 *
 * How to teach it?
 *
 * First, begin with the setup-Routine, only. Leave the loop-Routine empty.
 * Let the LED blink once a time on start/reset your Arduino
 * After this part is clear for the trainee, add the micro button circuit.
 * Than introduce the loop-Routine reading the button state. 
 *
 */
 
// Define your PIN layout here (macro constant)
#define PIN_LED 3
#define PIN_BTN 4

// needs 22 bytes more memory than a define constant
// int PIN_LED=3;
// int PIN_BTN=4;

// global variable for writing button state
int button_state;

void setup() {
  // Using for debugging
  Serial.begin(9600);
  
  // register your PIN usin pinMode(pin,O/I)
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BTN, INPUT);

  // short LED blink on startup sequence
  digitalWrite(PIN_LED, LOW);
  delay(500);
  digitalWrite(PIN_LED, HIGH);
  delay(500);
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  // read on button pin 
  button_state = digitalRead(PIN_BTN);  // return the button status HIGH or LOW
  Serial.println(button_state);
  
  // set LED PIN similar to button state
  digitalWrite(PIN_LED, button_state);
}
