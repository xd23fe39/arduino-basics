/**
 * RFID MFRC522 Read/Write Modul
 *
 *  
 */
#include <SPI.h> // SPI-Bibiothek hinzufügen
#include <MFRC522.h> // RFID-Bibiothek hinzufügen

#define APPLICATION_MODE "DEMO"

#define MAX_NTAGS 7
#define SECURITY_VERIFY_TAG

#define SS_PIN 10 // SDA an Pin 10 (UNO)
#define RST_PIN 9 // RST an Pin 9 (UNO)

void dump_byte_array(byte *buffer, byte bufferSize);
void array_to_string(byte array[], unsigned int len, char buffer[]);
bool verifyTAG(String masterID);


MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger initialisieren

struct NTAG {
  String ID;
  String Name;
  String SignerID;
  bool Active;
  unsigned long Used;
};

String MasterTAG = "79829B63";
String DemoTag = "048B279ABF5B80";
String RegisteredTAG = "";

// Signer NTAG 
NTAG SignerNTAG = {"79829B63", "MASTER_NTAG", "79829B63", true, 0};

// Liste der registrierten NTAGs 
NTAG NTAG_Items[MAX_NTAGS];

void relais_init(uint8_t pin, bool low_level_trigger = false);
void relais_switch(uint8_t pin, int level);

/**
 * Initialisierung des Relais. Es werden HIGH- und LOW-Level-Trigger
 * Relaismodule unterstützt. 
 */
void relais_init(uint8_t pin, bool low_level_trigger)
{
  // Anschluss-PIN als Ausgang setzen
  pinMode(pin, OUTPUT);
  
  // Low-Level-Trigger Module schalten beim Wechsel nach LOW 
  if (low_level_trigger)
  {
    relais_switch(pin, HIGH);    // AUS
  }
  else
  {
    relais_switch(pin, LOW);     // AUS
  }  
}

/**
 * Schaltet das Relaimodul an PIN pin auf LEVEL level.
 */
void relais_switch(uint8_t pin, int level)  
{
  digitalWrite(pin, level);
}

/**
 * MFRC522 Reader Demonstration Mode für NTAG UID.
 * 
 * Auslesen der NTAG UID.  
 */
void application_ntag_demo() {

  char buffer[10];

  Serial.println("Anwendung im NTAG Reader Demo-Modus. Warte auf NTAG...");

  while (true) { 

    if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
      Serial.print("MFRC522 UID Record - Size ");
      Serial.print(mfrc522.uid.size);
      Serial.print(" Type (SAK) ");
      Serial.print(mfrc522.PICC_GetType(mfrc522.uid.sak));
      array_to_string(mfrc522.uid.uidByte, mfrc522.uid.size, buffer);
      Serial.print(" Buffer ");
      Serial.print(buffer);
      Serial.print(" uidByte (MSB-LSB) ");
      uint8_t size = mfrc522.uid.size;
      for (uint8_t i = 0; i < size; i++) { 
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        Serial.print((i == size - 1) ? " (EOL) \n" : ":" );
      }
      if (DemoTag.equals(buffer)) 
      {
        relais_switch(8, LOW);
        delay(8000);
        relais_switch(8, HIGH);
      }
    }
    delay(200);
  }

  Serial.println();
  delay(3000);
}

/**
 * Registrieren eines neuen TAGs.
 */ 
void registerNewTag(String &tagID) {

    Serial.println("Registrieren Sie ihren TAG:");

    // Wenn Karte/Tag in Reichweite und SPI Signal zum lesen vorhanden...
    while ( RegisteredTAG == "" ) {
      if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        char code[48];
        array_to_string(mfrc522.uid.uidByte, mfrc522.uid.size, code);
        Serial.print("Neuer TAG erkannt. Code: ");
        Serial.print(code);
        Serial.println();

#ifdef SECURITY_VERIFY_TAG        
        if (verifyTAG(MasterTAG)) {
#endif
          tagID = code;
          Serial.print("Ihr Tag wurde registriert. Code: ");
          Serial.print(tagID);
          Serial.println();
          delay(2000);
          Serial.print("Sie können Ihre Tags jetzt ausprobieren...");
          Serial.println();

#ifdef SECURITY_VERIFY_TAG        
        }
#endif

      }
    }
}

bool verifyTAG(String masterID) {

    Serial.println("Bestätigen Sie mit dem Master-TAG (blau):");
    delay(2000);

    int timer = 15;

    // Wenn Karte/Tag in Reichweite und SPI Signal zum lesen vorhanden...
    while ( timer < 50 ) {
      if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {
        char code[48];
        array_to_string(mfrc522.uid.uidByte, mfrc522.uid.size, code);
        if (masterID.compareTo(code) == 0 ) {
          Serial.print("Bestätigung erfolgreich. ");
          Serial.print(code);
          Serial.println();
          return true;
        }
        else {
          Serial.print("Autorisierung fehlgeschlagen! ");
          Serial.print(code);
          Serial.println();
          return false;
        }
      }
      delay(200);
      timer++;
    }
    Serial.print("Verifizierung abgebrochen (Zeitlimit erreicht).");
    Serial.println();
    delay(2000);
    return false;
}

void setup() {
  // Initialisierung
  Serial.begin(9600);     // Serielle Verbindung starten (Monitor)
  SPI.begin();            // SPI-Verbindung aufbauen
  mfrc522.PCD_Init();     // Initialisierung des RFID-Empfängers

  relais_init(8, true);

  // Ausgabe an Serial Monitor
  Serial.println("\nRFID MFRC522 NTAG Demo");

  // Dump des Versionscodes / Versionsnummer  
  mfrc522.PCD_DumpVersionToSerial();

  // Auslesen des Versionscodes aus Test-Registern des MFRC522 (0x92 == Version 2.0)
  byte ver = mfrc522.PCD_ReadRegister(MFRC522::VersionReg);
  Serial.print("\nMFRC522 VersionReg ");
  Serial.print(ver,HEX);
  Serial.println();
}


void loop() {

// Application NTAG Reader Demo Modus 
#ifdef APPLICATION_MODE == "DEMO"
  application_ntag_demo();
  return;
#elif

  // Neues TAG registrieren, falls noch keines bekannt ist
  if (RegisteredTAG == "") {
    registerNewTag(RegisteredTAG);
  }

  // Wenn Karte/Tag in Reichweite und SPI Signal zum lesen vorhanden...
  if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {

    char code[48];
    array_to_string(mfrc522.uid.uidByte, mfrc522.uid.size, code);
    
    if (RegisteredTAG == code) {
      Serial.print("Registrierten Schlüssel erkannt! ");
      Serial.print(code);
      Serial.println();
    } 
    else {
      Serial.print("TAG ist nicht bekannt!");
      Serial.println();      
    }

    delay(2000);
  }

#endif
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.print(" Size ");
  Serial.print(bufferSize);
}

void array_to_string(byte array[], unsigned int len, char buffer[]) {
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}