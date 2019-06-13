/**
 * RFID MFRC522 Read/Write Modul
 *
 *  
 */
#include <SPI.h> // SPI-Bibiothek hinzufügen
#include <MFRC522.h> // RFID-Bibiothek hinzufügen

#define SS_PIN 10 // SDA an Pin 10 (UNO)
#define RST_PIN 9 // RST an Pin 9 (UNO)

void dump_byte_array(byte *buffer, byte bufferSize);
void array_to_string(byte array[], unsigned int len, char buffer[]);

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger initialisieren

void setup() {
  // Initialisierung
  Serial.begin(9600);     // Serielle Verbindung starten (Monitor)
  SPI.begin();            // SPI-Verbindung aufbauen
  mfrc522.PCD_Init();     // Initialisierung des RFID-Empfängers

  // Ausgabe an Serial Monitor
  Serial.println("\nRFID MFRC522 Read/Write Modul Demo");

  // Dump des Versionscodes / Versionsnummer  
  mfrc522.PCD_DumpVersionToSerial();

  // Auslesen des Versionscodes aus Test-Registern des MFRC522 (0x92 == Version 2.0)
  byte ver = mfrc522.PCD_ReadRegister(MFRC522::VersionReg);
  Serial.print("\nMFRC522 VersionReg ");
  Serial.print(ver,HEX);
  Serial.println();
}


void loop() {

  // Wenn Karte/Tag in Reichweite und SPI Signal zum lesen vorhanden...
  if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {

    // Ausgabe an Serial Monitor startet
    Serial.print("RFID-TAGS erkannt: ID ");

    // Auslesen...
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);    

    char code[48];
    array_to_string(mfrc522.uid.uidByte, mfrc522.uid.size, code);
    Serial.print(" - Code: ");
    Serial.print(code);
    Serial.println();

    delay(2000);
  }
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

void array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}