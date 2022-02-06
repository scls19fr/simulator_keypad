// ToDo: to test

#include <Keyboard.h>
#define KEY_KP_1          0xE1
#define KEY_KP_2          0xE2
#define KEY_KP_3          0xE3
#define KEY_KP_4          0xE4
#define KEY_KP_5          0xE5
#define KEY_KP_6          0xE6
#define KEY_KP_7          0xE7
#define KEY_KP_8          0xE8
#define KEY_KP_9          0xE9
#define KEY_KP_0          0xEA

// Analog keypad 4x4
// put A0 to GND to hardware disable analog keypad 4x4 or uncomment this line
// #define DISABLE_ANALOG_KEYPAD_4x4 1
#define PIN_ANALOG_KEYPAD_4x4 A0
#define NO_PRESS_VALUE_KEYPAD_4X4 0
#define USED_BUTTONS_KEYPAD_4X4 16
uint16_t values_keypad_4x4[USED_BUTTONS_KEYPAD_4X4] = {1023, 930, 852, 786, 675, 632, 596, 563, 502, 478, 457, 437, 400, 321, 269, 231};
#define TOLERANCE_KEYPAD_4X4 10

// Analog keypad 5 buttons
// put A1 to 5V to hardware disable analog keypad 5 buttons or uncomment this line
// #define DISABLE_ANALOG_KEYPAD_5BUT 1
#define PIN_ANALOG_KEYPAD_5BUT A1
#define NO_PRESS_VALUE_KEYPAD_5B 1023
#define USED_BUTTONS_KEYPAD_5B 5
uint16_t values_keypad_5b[USED_BUTTONS_KEYPAD_5B] = {0, 145, 330, 506, 742};
#define TOLERANCE_KEYPAD_5B 10

void setup() {
  Serial.begin(9600);

  Keyboard.begin();
}

uint16_t analogValue_keypad_4x4;
uint8_t button_4x4;
uint16_t analogValue_keypad_5b;
uint8_t button_k5;


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
#ifndef DISABLE_ANALOG_KEYPAD_4x4
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
#endif

#ifndef DISABLE_ANALOG_KEYPAD_5BUT

  analogValue_keypad_5b = analogRead(PIN_ANALOG_KEYPAD_5BUT);
  /*
   * if (!(nearFrom(analogValue_keypad_5b, NO_PRESS_VALUE_KEYPAD_5B, TOLERANCE_KEYPAD_5B))) {
   *   Serial.print("analogValue="); Serial.println(analogValue); 
   * }
   */

  button_k5 = USED_BUTTONS_KEYPAD_5B;
  for (uint8_t i=0;i<USED_BUTTONS_KEYPAD_5B;i++) {
    if (nearFrom(analogValue_keypad_5b, values_keypad_5b[i], TOLERANCE_KEYPAD_5B)) {
      button_k5 = i;
      break;
    }
  }
  
  if (button_k5 != USED_BUTTONS_KEYPAD_5B) {
    // Serial.print("The button "); Serial.print(button_k5); Serial.println(" is pressed");
    switch (button_k5) {
      case 1:
        //Serial.println("UP");
        // Keyboard.press(KEY_UP_ARROW);
        Keyboard.press(KEY_KP_8);
        break;
      case 2:
        // Serial.println("DOWN");
        // Keyboard.press(KEY_DOWN_ARROW);
        Keyboard.press(KEY_KP_2);
        break;
      case 0:
        // Serial.println("LEFT");
        // Keyboard.press(KEY_LEFT_ARROW);
        //Keyboard.press(KEY_KP_4);
        break;
      case 3:
        // Serial.println("RIGHT");
        // Keyboard.press(KEY_RIGHT_ARROW);
        Keyboard.press(KEY_KP_6);
        break;
      case 4:
        // Serial.println("BUT");
        Keyboard.press('p');
        break;
      default:
        break;
    }
    delay(200);
    Keyboard.releaseAll();
  }
#endif
}
