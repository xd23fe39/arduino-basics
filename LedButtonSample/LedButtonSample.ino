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
#define PIN_LED 12
#define PIN_BTN 7

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
  // read the input pin and write and output result to
  button_state = digitalRead(PIN_BTN);
  Serial.println(button_state);
  
  // switch LED on/off comparing button state
  if (button_state == HIGH) {
    digitalWrite(PIN_LED, HIGH);
  }
  else {
    digitalWrite(PIN_LED, LOW);
  }
}
