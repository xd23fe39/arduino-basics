/*

  MFRC522 Demo 


 */
#include <Arduino.h>
#include <SPI.h>        // SPI-Bibiothek hinzufügen
#include <MFRC522.h>    // RFID-Bibiothek hinzufügen

#define RC522_SDA_UNO   10
#define RC522_RST_UNO   9

MFRC522 mfrc522(RC522_SDA_UNO, RC522_RST_UNO); // RFID-Empfänger initialisieren

void setup() 
{

  Serial.begin(9600);     // Serielle Verbindung starten (Monitor)
  SPI.begin();            // SPI-Verbindung aufbauen
  mfrc522.PCD_Init();     // Initialisierung des RFID-Empfängers
  
  Serial.println("\nMFRC522 Tester Version 1.0\n");
}

void loop() 
{
  if ( mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) 
  {
    // Anzeige des UID Records
    Serial.println("MFRC522 - New Card Present. Read card serial...");
    Serial.print("MFRC522 UID Record, Size ");
    Serial.print(mfrc522.uid.size);
    Serial.print(" bytes ");
    // UID anzeigen via Hardware Serial
    for (byte n = 0; n < mfrc522.uid.size - 1; n++)
    {
      Serial.print(mfrc522.uid.uidByte[n], HEX);
      Serial.print(":");
    }
    Serial.print(mfrc522.uid.uidByte[mfrc522.uid.size-1], HEX);
    Serial.print(" type ");
    Serial.print(mfrc522.PICC_GetType(mfrc522.uid.sak));
    Serial.println();
    // Dump card information
    mfrc522.PICC_DumpToSerial(&mfrc522.uid);
    delay(2000);
  }
}
