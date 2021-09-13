#include "Frequency.h"
#include "KeyBuffer.h"
#include "Notes.h"

// SETTINGS
int octave = 2;
bool printToSerial = false;

const int CYCLES_PER_GLIDE_MAX = printToSerial ? 25 : 250;
const int STARTING_NOTE_DISTANCE_FROM_MIDDLE_A = -9;

const int SPEAKER_PIN = 11;

Notes notes(STARTING_NOTE_DISTANCE_FROM_MIDDLE_A);
KeyBuffer buffer;

void blink(int count = 2, int wait = 200) {
  while (count >= 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(wait);
    digitalWrite(LED_BUILTIN, LOW);
    delay(wait);

    count = count - 1;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  blink();
}

int ptr = 0;
int ctr = 0;
#define CTR_MAX 40
void loop() {
  buffer.populate();

  if (buffer.isEmpty()) {
    noTone(SPEAKER_PIN);
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    if (ptr > buffer.size()-1) {
      ptr = 0;
    }
    float f = notes.get(buffer.getNth(ptr));
    tone(SPEAKER_PIN, f);
    digitalWrite(LED_BUILTIN, HIGH);
    if (++ctr > CTR_MAX) {
      ptr++;
      ctr = 0;
    }
  }
}
