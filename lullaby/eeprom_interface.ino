// EEPROM structure of a melody:
// uint16_t melodyLength;
// uint8_t melodyPitches[melodyLength];
// uint16_t melodyDurations[melodyLength];

// An Arduino Nano has 1024 bytes of EEPROM memory.
// 2 bytes are reserved to store the melody length.
// Each note uses 3 bytes (1 for pitch, 2 for duration).
// This means that the maximum length of a melody is (1024-1) / 4 = 255 notes.

void saveDataToEeprom(Note melody[], uint16_t melodyLength) {
  Serial.println("Saving melody to EEPROM");
  EEPROM.update(0, melodyLength);
  for (uint8_t i = 0; i < melodyLength; i++) {
    Note note = melody[i];
    InMemoryNote inMemoryNote = getAddressForNote(i, melodyLength);
    EEPROM.put(inMemoryNote.pitchAddress, note.pitch);
    EEPROM.put(inMemoryNote.durationAddress, note.duration);
  }
}

uint16_t loadMelodyLengthFromEeprom() {
  return EEPROM.read(0);
}

Note* loadMelodyFromEeprom() {
  Serial.println("Loading melody from EEPROM");
  uint16_t melodyLength = loadMelodyLengthFromEeprom();
  Note* melody = new Note[melodyLength];

  for (uint8_t i = 0; i < melodyLength; i++) {
    InMemoryNote inMemoryNote = getAddressForNote(i, melodyLength);
    Note note;
    EEPROM.get(inMemoryNote.pitchAddress, note.pitch);
    EEPROM.get(inMemoryNote.durationAddress, note.duration);
    melody[i] = note;
  }
  return melody;
}

InMemoryNote getAddressForNote(int noteIndex, uint16_t melodyLength) {
  uint16_t memoryOffset = 100 * UNSIGNED_INT_SIZE;
  uint16_t melodySize = melodyLength * UNSIGNED_INT_SIZE;
  return (InMemoryNote) {
    (noteIndex * UNSIGNED_INT_SIZE) + UNSIGNED_SHORT_INT_SIZE + memoryOffset, (noteIndex * UNSIGNED_INT_SIZE) + UNSIGNED_SHORT_INT_SIZE + melodySize + memoryOffset
  };
}

void printEepromContent() {
  uint16_t melodyLength = loadMelodyLengthFromEeprom();
  Note* melody = loadMelodyFromEeprom();
  Serial.print("Melody length: ");
  Serial.println(melodyLength);
  Serial.print("Melody: ");
  for (uint8_t i = 0; i < melodyLength; i++) {
    Serial.print(melody[i].pitch);
    Serial.print(":");
    Serial.print(melody[i].duration);
    Serial.print(" ");
  }
  Serial.println();
}
