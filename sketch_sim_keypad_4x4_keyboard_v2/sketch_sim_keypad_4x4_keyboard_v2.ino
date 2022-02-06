#include <Keyboard.h>

#define PIN_ANALOG_KEYPAD_4x4 A0

#define NO_PRESS_VALUE_KEYPAD_4X4 0
#define USED_BUTTONS_KEYPAD_4X4 16
uint16_t values_keypad_4x4[USED_BUTTONS_KEYPAD_4X4] = {1023, 930, 852, 786, 675, 632, 596, 563, 502, 478, 457, 437, 400, 321, 269, 231};
#define TOLERANCE_KEYPAD_4X4 10

void setup() {
  Serial.begin(9600);

  Keyboard.begin();
}

uint16_t analogValue_keypad_4x4;
uint8_t button_4x4;

bool nearFrom(uint16_t val, uint16_t refVal, uint16_t tolerance) {
  uint16_t lower_bound, upper_bound;
  if (refVal >= tolerance) {
    lower_bound = refVal - tolerance;
  } else {
    lower_bound = 0;
  }
  upper_bound = refVal + tolerance;
  return (val >= lower_bound) && (val < upper_bound);
}

void loop() {
  analogValue_keypad_4x4 = analogRead(PIN_ANALOG_KEYPAD_4x4);
  // if (!(nearFrom(analogValue_keypad_4x4, NO_PRESS_VALUE_KEYPAD_4X4, TOLERANCE_KEYPAD_4X4))) {
    // Serial.print("analogValue="); Serial.println(analogValue);
    // Keyboard.releaseAll();
  // }

  button_4x4 = USED_BUTTONS_KEYPAD_4X4;
  for (uint8_t i = 0; i < USED_BUTTONS_KEYPAD_4X4; i++) {
    if (nearFrom(analogValue_keypad_4x4, values_keypad_4x4[i], TOLERANCE_KEYPAD_4X4)) {
      button_4x4 = i;
      break;
    }
  }

  // Serial.print("The button "); Serial.print((int)button_4x4); Serial.println(" is pressed");
  switch (button_4x4) {
    case 0:
      Keyboard.press('g');
      break;
    case 1:
      Keyboard.press('h');
      break;
    case 2:
      Keyboard.press('j');
      break;
    case 3:
      Keyboard.press('q');  // a=azerty -> q=qwerty
      break;
    case 4:
      Keyboard.press(KEY_F1);
      break;
    case 5:
      Keyboard.press(KEY_F2);
      break;
    case 6:
      Keyboard.press(KEY_F3);
      break;
    case 7:
      Keyboard.press(KEY_F4);
      break;
    case 8:
      Keyboard.press(KEY_END);
      break;
    case 9:
      Keyboard.press(KEY_HOME);
      break;
    case 10:
      Keyboard.press(KEY_F5);
      break;
    case 11:
      Keyboard.press(KEY_F6);
      break;
    case 12:
      Keyboard.press(KEY_PAGE_DOWN);
      break;
    case 13:
      Keyboard.press(KEY_PAGE_UP);
      break;
    case 14:
      Keyboard.press('m');  // ,=azerty -> m=qwerty
      break;
    case 15:
      Keyboard.press('y');
      break;
    default:
      break;
  }
  delay(200);
  Keyboard.releaseAll();

}
