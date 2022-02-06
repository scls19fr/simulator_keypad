#include <Keyboard.h>  // https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h
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

#define PIN_ANALOG_KEYPAD_5BUT A1

#define NO_PRESS_VALUE_KEYPAD_5B 1023
#define USED_BUTTONS_KEYPAD_5B 5
uint16_t values_keypad_5b[USED_BUTTONS_KEYPAD_5B] = {0, 145, 330, 506, 742};
#define TOLERANCE_KEYPAD_5B 10

void setup() {
  Serial.begin(9600);

  Keyboard.begin();
}

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
  analogValue_keypad_5b = analogRead(PIN_ANALOG_KEYPAD_5BUT);
  /*
   * if (!(nearFrom(analogValue, NO_PRESS_VALUE_KEYPAD_5B, TOLERANCE_KEYPAD_5B))) {
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
        Keyboard.press(KEY_KP_4);
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
}
