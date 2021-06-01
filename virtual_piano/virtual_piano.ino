#include "SR04.h"
#include "pitches.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
#define BUZZER_PIN 7

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

void setup() {
   Serial.begin(9600);
   delay(1000);
}

void playNote(int note) {
  tone(BUZZER_PIN, note);
  delay(250);
  noTone(BUZZER_PIN);
}

void loop() {
   long distance = sr04.Distance();

   // Plays a note according to the distance.
   if (a < 10) playNote(NOTE_C5);
   else if (a < 20) playNote(NOTE_D5);
   else if (a < 30) playNote(NOTE_E5);
   else if (a < 40) playNote(NOTE_F5);
   else if (a < 50) playNote(NOTE_G5);
   else noTone(BUZZER_PIN);

   // Prints the distance
   Serial.print(distance);
   Serial.println("cm");
}
