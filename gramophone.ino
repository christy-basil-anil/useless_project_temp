#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

// =====================================================
// PINS
// =====================================================

#define SS_PIN       5
#define RST_PIN      22
#define BUZZER_PIN   25
#define SERVO_PIN    26

// SPI
#define SCK_PIN      18
#define MISO_PIN     19
#define MOSI_PIN     23

// =====================================================
// RFID
// =====================================================

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

int startBlock = 4;

// =====================================================
// SERVO
// =====================================================

Servo myServo;

// =====================================================
// MELODY INFORMATION
// =====================================================

// Your original melody contains 94 integers
// Each integer = 2 bytes
// 94 × 2 = 188 bytes

#define MELODY_SIZE 94
#define TOTAL_BYTES 188

// =====================================================
// TEMPO
// =====================================================

int tempo = 144;

// Whole note duration
int wholenote = (60000 * 4) / tempo;

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // ===================================================
  // SPI FOR ESP32
  // ===================================================

  SPI.begin(
    SCK_PIN,
    MISO_PIN,
    MOSI_PIN,
    SS_PIN
  );

  // ===================================================
  // RFID
  // ===================================================

  rfid.PCD_Init();

  // ===================================================
  // BUZZER
  // ===================================================

  pinMode(BUZZER_PIN, OUTPUT);

  // ===================================================
  // SERVO
  // ===================================================

  myServo.setPeriodHertz(50);

  myServo.attach(
    SERVO_PIN,
    500,
    2400
  );

  // Start servo at center
  myServo.write(90);

  // ===================================================
  // RFID DEFAULT KEY
  // ===================================================

  // Default MIFARE Classic Key A
  // FF FF FF FF FF FF

  for (byte i = 0; i < 6; i++) {

    key.keyByte[i] = 0xFF;
  }

  // ===================================================
  // START MESSAGE
  // ===================================================

  Serial.println();
  Serial.println("==============================");
  Serial.println("     RFID MUSIC PLAYER");
  Serial.println("==============================");
  Serial.println();

  Serial.println("Place melody card...");
}

// =====================================================
// LOOP
// =====================================================

void loop() {

  // ===================================================
  // CHECK CARD
  // ===================================================

  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // ===================================================
  // READ CARD
  // ===================================================

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // ===================================================
  // CARD DETECTED
  // ===================================================

  Serial.println();
  Serial.println("******************************");
  Serial.println("       CARD DETECTED!");
  Serial.println("******************************");

  // ===================================================
  // READ AND PLAY
  // ===================================================

  readAndPlayMelody();

  // ===================================================
  // STOP RFID
  // ===================================================

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  // ===================================================
  // STOP BUZZER
  // ===================================================

  noTone(BUZZER_PIN);

  // ===================================================
  // RESET SERVO
  // ===================================================

  myServo.write(90);

  Serial.println();
  Serial.println("==============================");
  Serial.println("       SONG FINISHED");
  Serial.println("==============================");
  Serial.println();

  Serial.println("Remove card.");

  delay(3000);

  Serial.println("Waiting for card...");
}

// =====================================================
// READ MELODY FROM RFID CARD
// =====================================================

void readAndPlayMelody() {

  byte data[TOTAL_BYTES];

  int bytePosition = 0;
  int currentBlock = startBlock;

  Serial.println();
  Serial.println("Reading melody from card...");

  // ===================================================
  // READ RFID BLOCKS
  // ===================================================

  while (bytePosition < TOTAL_BYTES) {

    // -------------------------------------------------
    // Skip sector trailer blocks
    // -------------------------------------------------

    if (currentBlock % 4 == 3) {

      Serial.print("Skipping trailer block ");
      Serial.println(currentBlock);

      currentBlock++;

      continue;
    }

    byte buffer[18];
    byte bufferSize = 18;

    MFRC522::StatusCode status;

    // -------------------------------------------------
    // AUTHENTICATE
    // -------------------------------------------------

    status = rfid.PCD_Authenticate(
      MFRC522::PICC_CMD_MF_AUTH_KEY_A,
      currentBlock,
      &key,
      &(rfid.uid)
    );

    if (status != MFRC522::STATUS_OK) {

      Serial.print("Authentication failed at block ");
      Serial.println(currentBlock);

      return;
    }

    // -------------------------------------------------
    // READ BLOCK
    // -------------------------------------------------

    status = rfid.MIFARE_Read(
      currentBlock,
      buffer,
      &bufferSize
    );

    if (status != MFRC522::STATUS_OK) {

      Serial.print("Read failed at block ");
      Serial.println(currentBlock);

      return;
    }

    Serial.print("Read block ");
    Serial.println(currentBlock);

    // -------------------------------------------------
    // COPY 16 DATA BYTES
    // -------------------------------------------------

    for (
      byte i = 0;
      i < 16 && bytePosition < TOTAL_BYTES;
      i++
    ) {

      data[bytePosition] = buffer[i];

      bytePosition++;
    }

    currentBlock++;
  }

  // ===================================================
  // PLAY MELODY
  // ===================================================

  Serial.println();
  Serial.println("==============================");
  Serial.println("       PLAYING SONG");
  Serial.println("==============================");
  Serial.println();

  // ===================================================
  // SERVO SETTINGS
  // ===================================================

  int servoAngle = 0;

  // Servo movement amount
  int servoDirection = 5;

  // Start servo at 0 degrees
  myServo.write(servoAngle);

  // ===================================================
  // PLAY ALL MELODY DATA
  // ===================================================

  for (int i = 0; i < MELODY_SIZE; i++) {

    // -------------------------------------------------
    // RECONSTRUCT 16-BIT INTEGER
    // -------------------------------------------------

    byte low =
      data[i * 2];

    byte high =
      data[i * 2 + 1];

    int16_t value =
      (int16_t)((high << 8) | low);

    // -------------------------------------------------
    // EVERY TWO VALUES:
    //
    // frequency
    // duration
    //
    // Example:
    //
    // 294, 4
    // -------------------------------------------------

    if (i % 2 == 0) {

      int frequency = value;

      // ------------------------------------------------
      // GET DURATION
      // ------------------------------------------------

      byte durationLow =
        data[(i + 1) * 2];

      byte durationHigh =
        data[(i + 1) * 2 + 1];

      int16_t divider =
        (int16_t)((durationHigh << 8) | durationLow);

      // ------------------------------------------------
      // CALCULATE NOTE DURATION
      // ------------------------------------------------

      int noteDuration;

      if (divider > 0) {

        noteDuration =
          wholenote / divider;
      }

      else if (divider < 0) {

        noteDuration =
          wholenote / abs(divider);

        // Dotted note
        noteDuration =
          noteDuration * 3 / 2;
      }

      else {

        noteDuration = 0;
      }

      // ------------------------------------------------
      // SERIAL OUTPUT
      // ------------------------------------------------

      Serial.print("Frequency: ");
      Serial.print(frequency);

      Serial.print(" Hz   Duration: ");
      Serial.print(noteDuration);

      Serial.println(" ms");

      // =================================================
      // PLAY NOTE
      // =================================================

      if (frequency == 0) {

        noTone(BUZZER_PIN);
      }

      else {

        tone(
          BUZZER_PIN,
          frequency,
          noteDuration
        );
      }

      // =================================================
      // SERVO MOVEMENT
      // =================================================

      servoAngle += servoDirection;

      // Reached 180°
      if (servoAngle >= 180) {

        servoAngle = 180;

        servoDirection = -5;
      }

      // Reached 0°
      if (servoAngle <= 0) {

        servoAngle = 0;

        servoDirection = 5;
      }

      myServo.write(servoAngle);

      // =================================================
      // NOTE DELAY
      // =================================================

      int pauseBetweenNotes =
        noteDuration * 1.30;

      delay(pauseBetweenNotes);

      // =================================================
      // STOP NOTE
      // =================================================

      noTone(BUZZER_PIN);
    }
  }

  // ===================================================
  // SONG FINISHED
  // ===================================================

  noTone(BUZZER_PIN);

  // Return servo to center
  myServo.write(90);

  Serial.println();
  Serial.println("Song finished!");
}