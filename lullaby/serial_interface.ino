void printMenu() {
  // TODO: fix menu
  Serial.println(); 
  Serial.println(F("Smart carillon"));
  Serial.println(F("Note format is <pitch>:<duration>. Available commands:"));
  Serial.println(F("n <note_1> <note_2> ... <note_n>: plays the given notes"));
  Serial.println(F("s <note_1> <note_2> ... <note_n>: saves the given melody into EEPROM"));
  Serial.println(F("p: plays the current melody"));
  Serial.println(F("e: prints the EEPROM content"));
  Serial.println();
}

void handleMenuInput() {
  //   6 char per note atm
  char inputBuffer[323] = {};
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
  Serial.println(F("OK"));
  printMenu();
}

void saveMelodyFromSerial(char* msgBuffer) {
  Note melodyBuffer[MAX_MELODY_LENGTH] = {};
  MelodyInfo melodyInfo = parseMelody(msgBuffer, melodyBuffer);
  saveDataToEeprom(melodyBuffer, melodyInfo);
}

void playNotes(char* msgBuffer) {
  Serial.println(F("Play notes"));
  Note melodyBuffer[MAX_MELODY_LENGTH] = {};
  MelodyInfo melodyInfo = parseMelody(msgBuffer, melodyBuffer);
  playMelody(melodyBuffer, melodyInfo);
}
