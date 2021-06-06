void printMenu() {
  Serial.println("Smart carillon");
  Serial.println("Note format is <pitch>:<duration>. Available commands:");
  Serial.println("n <note_1> <note_2> ... <note_n>: plays the given notes");
  Serial.println("s <note_1> <note_2> ... <note_n>: saves the given melody into EEPROM");
  Serial.println("p: plays the current melody");
  Serial.println("e: prints the EEPROM content");
}

void handleMenuInput() {
    //   6 char per note atm
  char inputBuffer[323];
  Serial.readBytesUntil(SERIALIZED_EOS_CHAR, inputBuffer, 323);
  switch (inputBuffer[0]) {
    case 'n':
      playNotes(inputBuffer);
      break;
    case 's':
      saveMelodyFromSerial(inputBuffer);
      break;
    case 'p':
      playMelody();
      break;
    case 'e':
      printEepromContent();
      break;
  }
  Serial.println("OK");
  printMenu();
}

void saveMelodyFromSerial(char* msgBuffer) {
  Note melodyBuffer[MAX_MELODY_LENGTH];
  uint16_t melodyLength = parseNotes(msgBuffer, melodyBuffer);
  saveDataToEeprom(melodyBuffer, melodyLength);
}

uint16_t parseNotes(char* msgBuffer, Note* melodyBuffer){
  uint16_t melodyLength = 0;
  // Clears the buffer
  char* token = strtok(msgBuffer, " ");
  token = strtok(NULL, ":");
  while (token != NULL) {
    uint8_t pitch = atoi(token);

    token = strtok(NULL, " \n");
    uint16_t duration = atoi(token);

//    Serial.print(pitch);
//    Serial.print(":");
//    Serial.print(duration);
//    Serial.print(" ");

    melodyBuffer[melodyLength] = (Note) {
      pitch, duration
    };
    melodyLength++;
    token = strtok(NULL, ":");
  }
  return melodyLength;
}

void playNotes(char* msgBuffer) {
  Note melodyBuffer[MAX_MELODY_LENGTH];
  uint16_t melodyLength = parseNotes(msgBuffer, melodyBuffer);
  playMelody(melodyBuffer, melodyLength);
}
