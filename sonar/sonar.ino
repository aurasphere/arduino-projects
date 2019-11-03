//www.elegoo.com
//2016.12.08
#include "SR04.h"

#include "pitches.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

void setup() {
   Serial.begin(9600);
   delay(1000);
}

void loop() {
   a=sr04.Distance();

  int note;
   if (a < 30) {
      if (a > 25) note = NOTE_C5;
      else if (a > 20) note = NOTE_D5;
      else if (a > 15) note = NOTE_E5;
      else if (a > 10) note = NOTE_F5;
      else if (a > 5) note = NOTE_G5;
      else note = NOTE_A5;
      tone(7, note);
    } else noTone(7);
   Serial.print(a);
   Serial.println("cm");
  
}
