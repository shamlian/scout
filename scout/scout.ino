/*
   WiP
*/

#include <Keypad.h>

int speakerPin = 12;

const byte ROWS = 4;
const byte COLS = 4;
byte key_indexes[ROWS][COLS] = {
  {0, 4, 8, 12},
  {1, 5, 9, 13},
  {2, 6, 10, 14},
  {3, 7, 11, 15}
};
float notes[] = {523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245};
byte rowPins[ROWS] = {6, 10, 11, 4};
byte colPins[COLS] = {8, 5, 3, 7};

Keypad buttons = Keypad( makeKeymap(key_indexes), rowPins, colPins, ROWS, COLS );

float frequency = 0;
bool isActive = false;

void populateFrequencyAndIsActive() {
  isActive = false;

  buttons.getKeys(); // populate keys

  for (int i = 0; i < LIST_MAX; i++) {
    byte kstate = buttons.key[i].kstate;

    if (kstate == PRESSED || kstate == HOLD) {
      frequency = notes[buttons.key[i].kchar];
      isActive = true;
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  buttons.setDebounceTime(1); // 1 is the library's minimum debounce
}

void loop() {
  populateFrequencyAndIsActive();

  if (isActive) {
    Serial.println(String(frequency));
    tone(speakerPin, frequency);
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    noTone(speakerPin);
    digitalWrite(LED_BUILTIN, LOW);
  }
}
