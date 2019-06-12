/**
 * RFID MFRC522 Read/Write Modul
 *
 *  
 */
#include <SPI.h> // SPI-Bibiothek hinzufügen
#include <MFRC522.h> // RFID-Bibiothek hinzufügen

#define SS_PIN 10 // SDA an Pin 10 (UNO)
#define RST_PIN 9 // RST an Pin 9 (UNO)

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger initialisieren


void setup() {
  Serial.begin(9600); // Serielle Verbindung starten (Monitor)

  SPI.begin(); // SPI-Verbindung aufbauen

  mfrc522.PCD_Init(); // Initialisierung des RFID-Empfängers

}


void loop() {

  // Wenn Karte/Tag in Reichweite und SPI Signal zum lesen vorhanden...
  if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {

    // Ausgabe an Serial Monitor startet
    Serial.print("Die ID des RFID-TAGS lautet: ");

    // Auslesen...
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i], HEX); // Dann wird die UID ausgelesen, die aus vier einzelnen Blöcken besteht und der Reihe nach an den Serial Monitor gesendet. Die Endung Hex bedeutet, dass die vier Blöcke der UID als HEX-Zahl (also auch mit Buchstaben) ausgegeben wird
      Serial.print(" "); // Der Befehl „Serial.print(" ");“ sorgt dafür, dass zwischen den einzelnen ausgelesenen Blöcken ein Leerzeichen steht.
    }
    Serial.println(); // Mit dieser Zeile wird auf dem Serial Monitor nur ein Zeilenumbruch gemacht.
  }
}