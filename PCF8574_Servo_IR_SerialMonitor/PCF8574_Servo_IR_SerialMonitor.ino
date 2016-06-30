/**
 * Demo: setzt den Servo in Bewegung, wenn P4 oder P5 des Expanders mit GND verbunden sind.
 *
 * Baustein: PCF8574 IO Erweiterungskarte I/O I2C-Bus Modul Leichtbau Expansion Board TE255
 * The PCF8574 IO Expansion Board is an 8-bit remote I / O expander for I2C bus.
 * See also: http://www.nxp.com/documents/data_sheet/PCF8574.pdf
 *
 * Addressing:
 * Device Address (slave address): 0 
 *   7 bits: b0111AAA): 0x38 (if A2-A0 => b000)
 *
 * I2C am Arduino Nano:
 * Vcc  -  5V
 * GND  -  GND
 * SDA  -  A4
 * SCL  -  A5
 *
 * http://wiring.org.co/reference/libraries/Wire/index.html
 *
 * IR Receiver (VS1838B TL1838 1838 Infrared Receiver Head Universal IR Receiver 38kHz):
 * OUT  -  D11
 * GND  -  GND
 * Vcc   -  5V
 * 
 * IR Diode:
 * Vcc  -  D3  (Resistor: 100 Ohm erforderlich)
 * GND  -  GND
 *
 * Micro Servo (SG90):
 * GND   -  GND
 * Vcc   -  5V
 * PWM   -  PWM on Pins 3, 5, 6, 9, 10, and 11
 *
 * Required for IR:
 * http://z3t0.github.io/Arduino-IRremote/
 * https://github.com/z3t0/Arduino-IRremote
 *  
 * LED: 13. There is a built-in LED connected to digital pin 13.
 *
 * Created: 2016/06/28 Frank
 */
 
#include <Wire.h>
#include <Servo.h>
#include <IRremote.h>

#define PIN_IR_RECV 11
#define PIN_IR_SEND 3
#define PIN_BUILTIN_LED 13

#define PIN_SEND_FREQ 38

// ===================================================================
// Global variables
// =================================================================== 

Servo servos[1];
IRrecv irrecv(PIN_IR_RECV);
IRsend irsend;
int address = 0x38;    // 0x38 = Address Bits A2-A0: b000 
int error = 0;         // error code
uint8_t data = 0;      // 0xFF = alle PINs HIGH; 0xEF = P0 ist mit GND verbunden 

// ===================================================================
// Servo tool functions
// =================================================================== 

// merke letzte Position
int pos;

void servo_test(Servo* myservo, int min = 40, int max = 140 ) {

  for(pos = min; pos < max; pos += 1) {                                  
    myservo->write(pos);             
    delay(15);                       
  } 
  for(pos = max; pos>=min; pos-=1) {                                
    myservo->write(pos);              
    delay(15);                       
  }
} 

void servo_start(Servo* myservo, int start = 90) {

  if ( pos < start ) {
    for(; pos < start; pos += 1) {                                  
      myservo->write(pos);             
      delay(15);                       
    } 
  }
  if (pos > start) {
    for(; pos > start; pos-=1) {                                
      myservo->write(pos);              
      delay(15);                       
    }
  }
} 

// ===================================================================
// Arduino Setup
// =================================================================== 

void setup()
{
  Serial.begin(9600);
  Serial.println("Using: PCF8574");
  Serial.println("https://www.arduino.cc/en/Reference/Wire");
  Serial.println("http://www.nxp.com/documents/data_sheet/PCF8574.pdf");
  Serial.println("Serial Monitoring is started.");
  Serial.println("Entering setup()-Function.");
  Serial.print("Current Date is: ");
  Serial.println(__DATE__);  

  // initialize i2c bus  
  Wire.begin(); // join i2c bus (address optional for master)

  // initialize servos
  servos[0].attach(9);  
  
  // Initialize IR 
  pinMode(PIN_IR_RECV, INPUT);
  pinMode(PIN_IR_SEND, OUTPUT);
  irsend.enableIROut(PIN_SEND_FREQ);
  irsend.mark(0);  
}

// ===================================================================
// Arduino Loop
// =================================================================== 

void loop()
{
  Wire.beginTransmission(address); // Beginne mit der Datenübertragung für Gerät (0x38)
                                // device address is specified in datasheet
  Wire.requestFrom(address, 1);                         
  if ( !Wire.available() ) {
#if defined(SERIAL_DEBUG)
    Serial.print("Wire available: ");
    Serial.print(address, HEX);  
    Serial.println(" [ERROR]");      
#endif
  }
  
  data = Wire.read();
#if defined(SERIAL_DEBUG)
  Serial.print("Debug data: ");
  Serial.println(data, HEX);  
#endif

  switch(data) {
  case 0xFF:
    Serial.println("All PCF Pins are not connected!"); 
    break;
  case 0xFE:
    Serial.println("PCF PIN: P0"); 
    break;
  case 0xFD:
    Serial.println("PCF PIN: P1"); 
    break;
  case 0xFB:
    Serial.println("PCF PIN: P2"); 
    break;
  case 0xF7:
    Serial.println("PCF PIN: P3"); 
    break;
  case 0xEF:
    Serial.println("PCF PIN: P4"); 
    servo_start(&servos[0]);
    break;
  case 0xDF:
    Serial.println("PCF PIN: P5"); 
    servo_start(&servos[0], 40);
    servo_test(&servos[0], 40, 180);
    break;
  case 0xBF:
    Serial.println("PCF PIN: P6"); 
    break;
  case 0x7F:
    Serial.println("PCF PIN: P7"); 
    break;
  }
                           
  error = Wire.endTransmission();     // stop transmitting
  if ( error != 0 ) {
    Serial.print("  Wire.endTransmission(): ");
    Serial.println(error);  
  }
  
  int irrec = digitalRead(PIN_IR_RECV);
  if (irrec) {
    digitalWrite(PIN_BUILTIN_LED, irrec);
    servo_start(&servos[0], 60);
    servo_test(&servos[0], 60, 120);
  }

  delay(1);
}

