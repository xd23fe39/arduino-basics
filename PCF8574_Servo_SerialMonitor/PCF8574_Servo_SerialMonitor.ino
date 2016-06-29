/**
 * Demo: PCF8574 IO Erweiterungskarte I/O I2C-Bus Modul Leichtbau Expansion Board TE255
 * The PCF8574 IO Expansion Board is an 8-bit remote I / O expander for I2C bus.
 * See also: http://www.nxp.com/documents/data_sheet/PCF8574.pdf
 *
 * Addressing:
 * Device Address (slave address): 0 
 *   7 bits: b0111AAA): 0x38 (if A2-A0 => b000)
 *
 * I2C am Arduino Nano:
 * VCC  -  5V
 * GND  -  GND
 * SDA  -  A4
 * SCL  -  A5
 *
 * Created: 2016/06/28 Frank
 */
 
#include <Wire.h>
#include <Servo.h>

// ===================================================================
// Global variables
// =================================================================== 

Servo servos[1];
int address = 0x38;    // 0x38 = Address Bits A2-A0: b000 
int error = 0;         // error code
uint8_t data = 0;      // 0xFF = alle PINs HIGH; 0xEF = P0 ist mit GND verbunden 

// ===================================================================
// Servo tool functions
// =================================================================== 

void servo_test(Servo* myservo) {

  for(int pos = 40; pos < 140; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo->write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(int pos = 140; pos>=40; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo->write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
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
    break;
  case 0xDF:
    Serial.println("PCF PIN: P5"); 
    servo_test(&servos[0]);
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

  delay(500);
}

