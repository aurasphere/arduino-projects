void printMenu() {
  Serial.println("Smart carillon");
  Serial.println("Select one of the following options by pressing the respective character:");
  Serial.println("n: insert a (N)ew melody");
  Serial.println("p: (P)lay current melody");
  Serial.println("i: (I)nteractive mode");
  Serial.println("e: print (E)EPROM content");
}

void handleMenuInput() {
  char menuSelection[3];
  Serial.readBytesUntil(SERIALIZED_EOS_CHAR, menuSelection, 3);
  switch (menuSelection[0]) {
    case 'i':
      interactiveMode();
      break;
    case 'n':
      saveMelodyFromSerial();
      break;
    case 'p':
      playMelody();
      break;
    case 'e':
      printEepromContent();
      break;
  }
  printMenu();
}

void saveMelodyFromSerial() {
  Serial.println("You can register a new melody by sending a sequence of values separed by whitespace. Each note is represented in format <pitch>:<duration>");
  Note melodyBuffer[MAX_MELODY_LENGTH];

  //   6 char per note atm
  int msgLength = 320;
  char msgBuffer[msgLength];

  waitForInput();

  Serial.readBytesUntil(SERIALIZED_EOS_CHAR, msgBuffer, msgLength);

  uint16_t melodyLength = 0;
  char* token;
  token = strtok(msgBuffer, ":");
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

  saveDataToEeprom(melodyBuffer, melodyLength);
  Serial.println("Succesfully saved melody");
}

void interactiveMode() {}

void clearSerial() {
  while (Serial.available() != 0) {
    Serial.read();
  }
}

void waitForInput() {
  while (Serial.available() == 0) {}
}
