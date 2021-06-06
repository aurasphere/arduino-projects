#include "pitches.h"
#include <EEPROM.h>

#define MAX_MELODY_LENGTH 255
#define SERIALIZED_PITCH_DURATION_SEPARATOR ':'
#define SERIALIZED_NOTES_SEPARATOR ' '
#define SERIALIZED_EOS_CHAR '\n'

// Constant sizes of variables
#define INT_SIZE sizeof(int)
#define UNSIGNED_INT_SIZE sizeof(uint16_t)
#define UNSIGNED_SHORT_INT_SIZE sizeof(uint8_t)

// Note types
#define NOTE_STANDARD 500
#define NOTE_HALF NOTE_STANDARD / 2
#define NOTE_DOUBLE NOTE_STANDARD * 2
#define NOTE_FULL NOTE_STANDARD * 4
#define NOTE_THREE_QUARTER NOTE_STANDARD + NOTE_HALF

// Button
#define BUTTON 6
#define BUZZER 7

// Leds
#define WHITE 8
#define BLUE 9
#define GREEN 10
#define YELLOW 11
#define RED 12

__attribute__((optimize("O0")))

// Stored on flash memory to save RAM.
const uint16_t NOTES[] PROGMEM = {NOTE_B0 , NOTE_C1 , NOTE_CS1 , NOTE_D1 , NOTE_DS1 , NOTE_E1 , NOTE_F1 , NOTE_FS1 , NOTE_G1 , NOTE_GS1 , NOTE_A1 , NOTE_AS1 , NOTE_B1 , NOTE_C2 , NOTE_CS2 , NOTE_D2 , NOTE_DS2 , NOTE_E2 , NOTE_F2 , NOTE_FS2 , NOTE_G2 , NOTE_GS2 , NOTE_A2 , NOTE_AS2 , NOTE_B2 , NOTE_C3 , NOTE_CS3 , NOTE_D3 , NOTE_DS3 , NOTE_E3 , NOTE_F3 , NOTE_FS3 , NOTE_G3 , NOTE_GS3 , NOTE_A3 , NOTE_AS3 , NOTE_B3 , NOTE_C4 , NOTE_CS4 , NOTE_D4 , NOTE_DS4 , NOTE_E4 , NOTE_F4 , NOTE_FS4 , NOTE_G4 , NOTE_GS4 , NOTE_A4 , NOTE_AS4 , NOTE_B4 , NOTE_C5 , NOTE_CS5 , NOTE_D5 , NOTE_DS5 , NOTE_E5 , NOTE_F5 , NOTE_FS5 , NOTE_G5 , NOTE_GS5 , NOTE_A5 , NOTE_AS5 , NOTE_B5 , NOTE_C6 , NOTE_CS6 , NOTE_D6 , NOTE_DS6 , NOTE_E6 , NOTE_F6 , NOTE_FS6 , NOTE_G6 , NOTE_GS6 , NOTE_A6 , NOTE_AS6 , NOTE_B6 , NOTE_C7 , NOTE_CS7 , NOTE_D7 , NOTE_DS7 , NOTE_E7 , NOTE_F7 , NOTE_FS7 , NOTE_G7 , NOTE_GS7 , NOTE_A7 , NOTE_AS7 , NOTE_B7 , NOTE_C8 , NOTE_CS8 , NOTE_D8 , NOTE_DS8};

struct Note {
  uint8_t pitch;
  uint16_t duration;
};

struct InMemoryNote {
  uint16_t pitchAddress;
  uint16_t durationAddress;
};

void setup() {
  // Open serial for communication.
  Serial.begin(9600);
  printMenu();

  // Inizializes LEDS (if available)
  for (uint8_t i = WHITE; i <= RED; i++) {
    pinMode(i, OUTPUT);
  }

  // Inizializes the button
  pinMode(BUTTON, INPUT_PULLUP);
}

void playMelody(Note* melody, uint16_t melodyLength) {
  for (uint8_t i = 0; i < melodyLength; i++) {
    Note note = melody[i];
    uint16_t pitch = pgm_read_word(NOTES + note.pitch);
    uint16_t duration = note.duration * 10;

    Serial.print(note.pitch);
    Serial.print(":");
    Serial.print(duration);

    // Plays a note.
    tone(BUZZER, pitch, duration);

    randomizeLeds();

    // Plays the note for the specified duration.
    delay(duration);
  }
  delete[] melody;
  clearLeds();
}


void playMelody() {
  Note* melody = loadMelodyFromEeprom();
  uint16_t melodyLength = loadMelodyLengthFromEeprom();
  playMelody(melody, melodyLength);
}

void loop() {

  // Handles a menu selection.
  if (Serial.available()) {
    handleMenuInput();
  }

  if (digitalRead(BUTTON) == LOW) {
    playMelody();
  }
}
