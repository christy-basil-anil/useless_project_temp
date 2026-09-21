#include <SPI.h> 
#include <MFRC522.h> 
#include <stdint.h> 
 
#define SS_PIN 10 
#define RST_PIN 9 
 
MFRC522 rfid(SS_PIN, RST_PIN); 
 
// ===================================================== 
// NOTES 
// ===================================================== 
 
#define REST 0 
 
#define NOTE_B0 31 
#define NOTE_C1 33 
#define NOTE_CS1 35 
#define NOTE_D1 37 
#define NOTE_DS1 39 
#define NOTE_E1 41 
#define NOTE_F1 44 
#define NOTE_FS1 46 
#define NOTE_G1 49 
#define NOTE_GS1 52 
#define NOTE_A1 55 
#define NOTE_AS1 58 
#define NOTE_B1 62 
#define NOTE_C2 65 
#define NOTE_CS2 69 
#define NOTE_D2 73 
#define NOTE_DS2 78 
#define NOTE_E2 82 
#define NOTE_F2 87 
#define NOTE_FS2 93 
#define NOTE_G2 98 
#define NOTE_GS2 104 
#define NOTE_A2 110 
#define NOTE_AS2 117 
#define NOTE_B2 123 
#define NOTE_C3 131 
#define NOTE_CS3 139 
#define NOTE_D3 147 
#define NOTE_DS3 156 
#define NOTE_E3 165 
#define NOTE_F3 175 
#define NOTE_FS3 185 
#define NOTE_G3 196 
#define NOTE_GS3 208 
#define NOTE_A3 220 
#define NOTE_AS3 233 
#define NOTE_B3 247 
#define NOTE_C4 262 
#define NOTE_CS4 277 
#define NOTE_D4 294 
#define NOTE_DS4 311 
#define NOTE_E4 330 
#define NOTE_F4 349 
#define NOTE_FS4 370 
#define NOTE_G4 392 
#define NOTE_GS4 415 
#define NOTE_A4 440 
#define NOTE_AS4 466 
#define NOTE_B4 494 
#define NOTE_C5 523 
#define NOTE_CS5 554 
#define NOTE_D5 587 
#define NOTE_DS5 622 
#define NOTE_E5 659 
#define NOTE_F5 698 
#define NOTE_FS5 740 
#define NOTE_G5 784 
#define NOTE_GS5 831 
#define NOTE_A5 880 
#define NOTE_AS5 932 
#define NOTE_B5 988 
#define NOTE_C6 1047 
#define NOTE_CS6 1109 
#define NOTE_D6 1175 
#define NOTE_DS6 1245 
#define NOTE_E6 1319 
#define NOTE_F6 1397 
#define NOTE_FS6 1480 
#define NOTE_G6 1568 
#define NOTE_GS6 1661 
#define NOTE_A6 1760 
#define NOTE_AS6 1865 
#define NOTE_B6 1976 
 
// ===================================================== 
// HEDWIG'S THEME 
// ===================================================== 
 
int melody[] = { 
 
  REST, 2, NOTE_D4, 4, 
 
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, 
  NOTE_G4, 2, NOTE_D5, 4, 
 
  NOTE_C5, -2, 
  NOTE_A4, -2, 
 
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, 
  NOTE_F4, 2, NOTE_GS4, 4, 
 
  NOTE_D4, -1, 
  NOTE_D4, 4, 
 
  NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, 
  NOTE_G4, 2, NOTE_D5, 4, 
 
  NOTE_F5, 2, NOTE_E5, 4, 
  NOTE_DS5, 2, NOTE_B4, 4, 
 
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4, 
  NOTE_CS4, 2, NOTE_B4, 4, 
 
  NOTE_G4, -1, 
  NOTE_AS4, 4, 
 
  NOTE_D5, 2, NOTE_AS4, 4, 
  NOTE_D5, 2, NOTE_AS4, 4, 
 
  NOTE_DS5, 2, NOTE_D5, 4, 
  NOTE_CS5, 2, NOTE_A4, 4, 
 
  NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4, 
  NOTE_CS4, 2, NOTE_D4, 4, 
 
  NOTE_D5, -1, 
  REST, 4, NOTE_AS4, 4, 
 
  NOTE_D5, 2, NOTE_AS4, 4, 
  NOTE_D5, 2, NOTE_AS4, 4, 
 
  NOTE_F5, 2, NOTE_E5, 4, 
  NOTE_DS5, 2, NOTE_B4, 4, 
 
  NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4, 
  NOTE_CS4, 2, NOTE_AS4, 4, 
 
  NOTE_G4, -1 
}; 
 
// ===================================================== 
// RFID KEY 
// ===================================================== 
 
MFRC522::MIFARE_Key key; 
 
// Data starts at block 4 
int startBlock = 4; 
 
// ===================================================== 
// SETUP 
// ===================================================== 
 
void setup() { 
 
  Serial.begin(9600); 
 
  SPI.begin(); 
  rfid.PCD_Init(); 
 
  // Default RFID key: 
  // FF FF FF FF FF FF 
 
  for (byte i = 0; i < 6; i++) { 
    key.keyByte[i] = 0xFF; 
  } 
 
  Serial.println(); 
  Serial.println("=============================="); 
  Serial.println(" RFID MELODY WRITER"); 
  Serial.println("=============================="); 
  Serial.println(); 
  Serial.println("Place your MIFARE Classic card..."); 
} 
 
// ===================================================== 
// LOOP 
// ===================================================== 
 
void loop() { 
 
  if (!rfid.PICC_IsNewCardPresent()) 
    return; 
 
  if (!rfid.PICC_ReadCardSerial()) 
    return; 
 
  Serial.println(); 
  Serial.println("Card detected!"); 
 
  // Show UID 
  Serial.print("UID: "); 
 
  for (byte i = 0; i < rfid.uid.size; i++) { 
    if (rfid.uid.uidByte[i] < 0x10) 
      Serial.print("0"); 
 
    Serial.print(rfid.uid.uidByte[i], HEX); 
    Serial.print(" "); 
  } 
 
  Serial.println(); 
 
  // Check card type 
  MFRC522::PICC_Type piccType = 
    rfid.PICC_GetType(rfid.uid.sak); 
 
  Serial.print("Card type: "); 
  Serial.println(rfid.PICC_GetTypeName(piccType)); 
 
  // Write melody 
  writeMelody(); 
 
  rfid.PICC_HaltA(); 
  rfid.PCD_StopCrypto1(); 
 
  Serial.println(); 
  Serial.println("Remove card."); 
  Serial.println(); 
 
  delay(3000); 
} 
 
// ===================================================== 
// WRITE MELODY 
// ===================================================== 
 
void writeMelody() { 
 
  int melodySize = sizeof(melody) / sizeof(melody[0]); 
 
  Serial.print("Melody integers: "); 
  Serial.println(melodySize); 
 
  Serial.print("Required bytes: "); 
  Serial.println(melodySize * 2); 
 
  // Each integer = 2 bytes 
  int totalBytes = melodySize * 2; 
 
  int currentBlock = startBlock; 
  int bytePosition = 0; 
 
  while (bytePosition < totalBytes) { 
 
    // Never write sector trailer 
    if (currentBlock % 4 == 3) { 
 
      Serial.print("Skipping trailer block "); 
      Serial.println(currentBlock); 
 
      currentBlock++; 
      continue; 
    } 
 
    byte buffer[16]; 
 
    // Clear block 
    for (byte i = 0; i < 16; i++) { 
      buffer[i] = 0; 
    } 
 
    // Fill 16-byte block 
    for (byte i = 0; i < 16 && bytePosition < totalBytes; i++) { 
 
      int integerIndex = bytePosition / 2; 
 
      if (bytePosition % 2 == 0) { 
 
        // LOW byte 
        buffer[i] = lowByte(melody[integerIndex]); 
 
      } else { 
 
        // HIGH byte 
        buffer[i] = highByte(melody[integerIndex]); 
      } 
 
      bytePosition++; 
    } 
 
    // Authenticate block 
    MFRC522::StatusCode status; 
 
    status = rfid.PCD_Authenticate( 
      MFRC522::PICC_CMD_MF_AUTH_KEY_A, 
      currentBlock, 
      &key, 
      &(rfid.uid) 
    ); 
 
    if (status != MFRC522::STATUS_OK) { 
 
      Serial.print("Authentication failed at block "); 
      Serial.print(currentBlock); 
      Serial.print(": "); 
 
      Serial.println(rfid.GetStatusCodeName(status)); 
 
      return; 
    } 
 
    // Write block 
    status = rfid.MIFARE_Write( 
      currentBlock, 
      buffer, 
      16 
    ); 
 
    if (status != MFRC522::STATUS_OK) { 
 
      Serial.print("Write failed at block "); 
      Serial.print(currentBlock); 
      Serial.print(": "); 
 
      Serial.println(rfid.GetStatusCodeName(status)); 
 
      return; 
    } 
 
    Serial.print("Written block "); 
    Serial.println(currentBlock); 
 
    currentBlock++; 
  } 
 
  Serial.println(); 
  Serial.println("================================"); 
  Serial.println("MELODY SUCCESSFULLY WRITTEN!"); 
  Serial.println("================================"); 
} 
