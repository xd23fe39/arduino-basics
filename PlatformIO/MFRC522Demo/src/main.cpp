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

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger initialisieren

void setup() {
  Serial.begin(9600); // Serielle Verbindung starten (Monitor)

  SPI.begin(); // SPI-Verbindung aufbauen

  mfrc522.PCD_Init(); // Initialisierung des RFID-Empfängers
  Serial.println("\nRFID MFRC522 Read/Write Modul Demo");
  mfrc522.PCD_DumpVersionToSerial();
}


void loop() {

  // Wenn Karte/Tag in Reichweite und SPI Signal zum lesen vorhanden...
  if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {

    // Ausgabe an Serial Monitor startet
    Serial.print("Die ID des RFID-TAGS lautet: ");

    // Auslesen...
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

    Serial.println(); // Mit dieser Zeile wird auf dem Serial Monitor nur ein Zeilenumbruch gemacht.

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
}