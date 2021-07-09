MelodyInfo parseMelody(char* msgBuffer, Note* melodyBuffer) {
  uint16_t melodyLength = 0;

  // Parses the header first
  char header[4] = {msgBuffer[1], msgBuffer[2], msgBuffer[3]};
  MelodyInfo melodyInfo = parseHeader(header);

  // Parses the single notes.
  char nextChar = msgBuffer[4];
  while (nextChar != NULL) {
    uint8_t notePointer = (melodyLength * 3) + 4;
    char noteChar[5] = {msgBuffer[notePointer], msgBuffer[notePointer + 1] , msgBuffer[notePointer + 2]};
    melodyBuffer[melodyLength] = parseNote(noteChar);
    melodyLength++;
    nextChar = msgBuffer[notePointer + 3];
  }

  melodyInfo.length = melodyLength;
  return melodyInfo;
}

// Each note is represented by 3 HEX char with the following content:
// 3 bit <- note
// 2 bit <- duration
// 3 bit <- octave
// 1 bit <- extended
// 1 bit <- altered
// 2 bit <- filler
Note parseNote(char* note) {
 // Serial.println(note);
  char firstByteArray[3] = {note[0], note[1]};
  char secondByteArray[2] = {note[2]};
  uint8_t firstByte = (uint8_t) strtol(firstByteArray, NULL, 16);
  uint8_t secondByte = (uint8_t) strtol(secondByteArray, NULL, 16);
  return  (Note) {
    applyMask(firstByte, 5, 3),
              applyMask(firstByte, 3, 2),
              applyMask(firstByte, 0, 3),
              isBitSet(secondByte, 3),
              isBitSet(secondByte, 2)
  };
}

// An header is represented by 3 characters:
// 2 HEX <- bpm
// 1 DEC <- the beat unit
//        1 = */2 (half note)
//        2 = */4 (quarter note)
//        3 = */8 (eight note)
MelodyInfo parseHeader(char* header) {
  char bpmHex[3] = {header[0], header[1]};
  uint8_t bpm = (uint8_t) strtol(bpmHex, NULL, 16);
  uint8_t beatNote = (uint8_t) strtol(&header[2], NULL, 10);
  return (MelodyInfo) {
    bpm, beatNote, 0
  };
}

uint8_t applyMask(uint8_t byteVal, uint8_t index, uint8_t bitsToMask) {
  uint16_t mask = 1;
  for (uint8_t i = 0; i < bitsToMask - 1; i++, mask = mask * 10 + 1);
  return (byteVal & (mask << index)) >> index;
}

boolean isBitSet(uint8_t byteVal, uint8_t index) {
  return (byteVal & (1 << index)) != 0;
}
