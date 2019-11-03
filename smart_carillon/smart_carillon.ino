#include "pitches.h"
#include <EEPROM.h>

// Constant sizes of variables
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

// Leds
#define WHITE 8
#define BLUE 9
#define GREEN 10
#define YELLOW 11
#define RED 12
 
// notes in the melody:
uint16_t jingleBells [] = {
  NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D6, NOTE_E5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_G5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_G5, NOTE_G5, NOTE_F5, NOTE_D5, NOTE_C5};
uint16_t notes[] = {
  NOTE_STANDARD, NOTE_STANDARD, NOTE_DOUBLE, NOTE_STANDARD, NOTE_STANDARD, NOTE_DOUBLE, NOTE_STANDARD, NOTE_STANDARD, NOTE_THREE_QUARTER, NOTE_HALF, NOTE_FULL, NOTE_STANDARD, NOTE_STANDARD, NOTE_THREE_QUARTER, NOTE_HALF, NOTE_STANDARD, NOTE_STANDARD, NOTE_STANDARD, NOTE_HALF, NOTE_HALF, NOTE_STANDARD, NOTE_STANDARD, NOTE_STANDARD, NOTE_STANDARD, NOTE_DOUBLE, NOTE_DOUBLE, NOTE_STANDARD, NOTE_STANDARD, NOTE_DOUBLE, NOTE_STANDARD, NOTE_STANDARD, NOTE_DOUBLE, NOTE_STANDARD, NOTE_STANDARD, NOTE_THREE_QUARTER, NOTE_HALF, NOTE_FULL, NOTE_STANDARD, NOTE_STANDARD, NOTE_STANDARD, NOTE_STANDARD, NOTE_STANDARD, NOTE_STANDARD, NOTE_STANDARD, NOTE_HALF, NOTE_HALF, NOTE_STANDARD, NOTE_STANDARD, NOTE_STANDARD, NOTE_STANDARD, NOTE_FULL };

void saveDataToEeprom() {
  uint16_t melodySize = sizeof(jingleBells);
  uint8_t melodyLength =  melodySize / UNSIGNED_INT_SIZE;
     Serial.print("Melody size: ");
      Serial.println(melodySize);
  Serial.print("Melody length: ");
  Serial.println(melodyLength);
  EEPROM.update(0, melodyLength);
  for (int i = 0; i < melodyLength; i++) {
     Serial.print(i);
        Serial.print(" : note= ");
        Serial.print(jingleBells[i]);
        Serial.print(" , type= ");
        Serial.println(notes[i]);
     EEPROM.put((i * UNSIGNED_INT_SIZE) + UNSIGNED_SHORT_INT_SIZE, jingleBells[i]);
     EEPROM.put((i * UNSIGNED_INT_SIZE) + UNSIGNED_SHORT_INT_SIZE + melodySize, notes[i]);
  }
}

void setup() {
  
Serial.begin(9600);
  for (int i = WHITE; i <= RED; i++) {
      pinMode(i, OUTPUT);
  }

  pinMode(BUTTON, INPUT_PULLUP);

  saveDataToEeprom();
}

void checkIncomingBluetoothConnection() {
   // Reads the input.
    while (Serial.available()) {
        inChar = (char) Serial.read(); 
        inputString += inChar;

        // Sends back the received string if any.
        if (inputString != "") {
            Serial.print(inputString);
            inputString = "";
        }
    }
}

boolean running = false;
boolean melodyLoaded = false;
void loop() {

    checkIncomingBluetoothConnection();
if (!running && digitalRead(BUTTON) == LOW) {
  uint8_t melodyLength = EEPROM.read(0);
  uint16_t melody[melodyLength];
  uint16_t melodyNotes[melodyLength];

  if (!melodyLoaded) {
    uint16_t melodySize = melodyLength * UNSIGNED_INT_SIZE;
      Serial.print("Melody size: ");
      Serial.println(melodySize);
  Serial.print("Melody length: ");
  Serial.println(melodyLength);
    for (int i = 0; i < melodyLength; i++) {
        EEPROM.get((i * UNSIGNED_INT_SIZE) + UNSIGNED_SHORT_INT_SIZE, melody[i]);
        EEPROM.get((i * UNSIGNED_INT_SIZE) + UNSIGNED_SHORT_INT_SIZE + melodySize, melodyNotes[i]);
      Serial.print(i);
        Serial.print(" : note= ");
        Serial.print(melody[i]);
        Serial.print(" , type= ");
        Serial.println(melodyNotes[i]);
    }
    melodyLoaded = true;    
  }

  running = true;
  for (int noteIdx = 0; noteIdx < melodyLength; noteIdx++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(7, melody[noteIdx], melodyNotes[noteIdx]);

    // Randomizes the leds color.
    for (int i = WHITE; i <= RED; i++) {
      digitalWrite(i, random(2));
    }
     
    // Output the voice after several minutes
    delay(melodyNotes[noteIdx]);
  }
   // Clears the leds.
    for (int i = WHITE; i <= RED; i++) {
      digitalWrite(i, LOW);
    }
  running = false;
 }
}
