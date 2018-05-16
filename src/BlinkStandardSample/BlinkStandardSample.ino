/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// loop counter
int lcnt = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // Output 
  Serial.begin(9600);
  Serial.print("Using LED PIN: ");
  Serial.println(led);
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
  // initialize PINs
  pinMode(2, OUTPUT);     
  pinMode(3, OUTPUT);     
  pinMode(4, OUTPUT);     
  pinMode(5, OUTPUT);     
  pinMode(6, OUTPUT);     
  pinMode(7, OUTPUT);     
  pinMode(8, INPUT);     
  pinMode(9, INPUT);     
  pinMode(10, INPUT);     
  pinMode(11, INPUT);  
  digitalWrite(2, LOW);   
  digitalWrite(3, LOW);   
  digitalWrite(4, LOW);   
  digitalWrite(5, LOW);   
  digitalWrite(6, LOW);   
  digitalWrite(7, LOW);   
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.print("|");
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  Serial.print(".");
  delay(1000);               // wait for a second
  if (++lcnt % 10 == 0) Serial.println(lcnt);
}
