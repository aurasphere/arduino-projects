#include "SR04.h"
#include "pitches.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
#define BUZZER_PIN 7
#define SR04_MAX_RANGE_CM 4000

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

void setup() {
   Serial.begin(9600);
   delay(1000);
}

void loop() {
   long distance = sr04.Distance();
   
   // Plays a sound according to the distance.
   tone(BUZZER_PIN, NOTE_C5);
   delay(250);
   noTone(BUZZER_PIN);
   delay(250 + (distance * 25));
  
   // Prints the distance
   Serial.print(distance);
   Serial.println("cm");
}
