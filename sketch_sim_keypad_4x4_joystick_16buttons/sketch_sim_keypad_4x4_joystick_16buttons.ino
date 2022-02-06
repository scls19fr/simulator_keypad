#include <Joystick.h>  // https://github.com/MHeironimus/ArduinoJoystickLibrary

#define PIN_ANALOG_KEYPAD_4x4 A0

#define USED_BUTTONS_KEYPAD_4X4 16
#define MAX_JOYSTICK_BUTTONS 32
#define NO_PRESS_VALUE_KEYPAD_4X4 0
uint16_t values_keypad_4x4[USED_BUTTONS_KEYPAD_4X4] = {1023, 930, 852, 786, 675, 632, 596, 563, 502, 478, 457, 437, 400, 321, 269, 231};
#define TOLERANCE_KEYPAD_4X4 10

// Joystick_ Joystick;
Joystick_ Joystick(0x03, //hid report id
  JOYSTICK_TYPE_GAMEPAD, //joystick type
  USED_BUTTONS_KEYPAD_4X4, //button count
  0, //Hsw 0-2
  false, //x
  false, //y
  false, //z
  false, //rx
  false, //ry
  false, //rz
  false, //rudder
  false, //throttle
  false, //accelerator
  false, //brake
  false); //steering

void unsetAllButtons() {
  for (uint8_t i=0;i<MAX_JOYSTICK_BUTTONS;++i) {
    Joystick.setButton(i, false);
  }
}

void setup() {
  Serial.begin(9600);

  Joystick.begin();
  unsetAllButtons();

  // Display values
  //for (uint8_t i=0;i<USED_BUTTONS;i++) {
  //  Serial.println(values[i]);
  //}

}

bool nearFrom(uint16_t val, uint16_t refVal, uint16_t tolerance) {
  uint16_t lower_bound, upper_bound;
  if (refVal >= tolerance) {
    lower_bound = refVal - tolerance;
  } else {
    lower_bound = 0;
  }
  upper_bound = refVal + tolerance;
  return val >= lower_bound && val < upper_bound;
}

uint16_t analogValue_keypad_4x4;

void loop() {
  analogValue_keypad_4x4 = analogRead(PIN_ANALOG_KEYPAD_4x4); 
  // Serial.print("analogValue="); Serial.println(analogValue);
  for (uint8_t i=0;i<USED_BUTTONS_KEYPAD_4X4;i++) {
    if (nearFrom(analogValue_keypad_4x4, values_keypad_4x4[i], TOLERANCE_KEYPAD_4X4)) {
      // Serial.print("key ");
      // Serial.print(i);
      // Serial.println(" pressed");
      Joystick.setButton(i, true);
    }
  }
  if (analogValue_keypad_4x4 < TOLERANCE_KEYPAD_4X4) {
    unsetAllButtons();
  }
  //delay(100);

}
