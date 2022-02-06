// #include <Keyboard.h>
#include <Joystick.h>  // https://github.com/MHeironimus/ArduinoJoystickLibrary

#define PIN_ANALOG_KEYPAD_5BUT A1

#define NO_PRESS_VALUE_KEYPAD_5B 1023
#define MAX_JOYSTICK_BUTTONS 32
#define USED_BUTTONS_KEYPAD_5B 5
uint16_t values_keypad_5b[USED_BUTTONS_KEYPAD_5B] = {0, 145, 330, 506, 742};
#define TOLERANCE_KEYPAD_5B 10

#define SW5_JOYBUT 0

// Joystick_ Joystick;
Joystick_ Joystick(0x03, //hid report id
  JOYSTICK_TYPE_GAMEPAD, //joystick type
  1, //button count
  1, //Hsw 0-2
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

void releaseHatSwitch() {
  Joystick.setHatSwitch(0, -1);
}

void setup() {
  Serial.begin(9600);

  //Keyboard.begin();
  Joystick.begin();
}

uint16_t analogValue_keypad_5b;
uint8_t button_k5;

bool nearFrom(uint16_t val, uint16_t refVal) {
  uint16_t lower_bound, upper_bound;
  if (refVal >= TOLERANCE_KEYPAD_5B) {
    lower_bound = refVal - TOLERANCE_KEYPAD_5B;
  } else {
    lower_bound = 0;
  }
  upper_bound = refVal + TOLERANCE_KEYPAD_5B;
  return val >= lower_bound && val < upper_bound;
}

void loop() {
  analogValue_keypad_5b = analogRead(PIN_ANALOG_KEYPAD_5BUT);
  if (!(nearFrom(analogValue_keypad_5b, NO_PRESS_VALUE_KEYPAD_5B))) {
    // Serial.print("analogValue="); Serial.println(analogValue);
  }
   
  button_k5 = USED_BUTTONS_KEYPAD_5B;
  for (uint8_t i=0;i<USED_BUTTONS_KEYPAD_5B;i++) {
    if (nearFrom(analogValue_keypad_5b, values_keypad_5b[i])) {
      button_k5 = i;
      break;
    }
  }
  
  if (button_k5 != USED_BUTTONS_KEYPAD_5B) {
    // Serial.print("The button "); Serial.print(button_k5); Serial.println(" is pressed");
    if (button_k5 == 4) {
        // Serial.println("BUT");
        Joystick.setButton(SW5_JOYBUT, true);
        //Keyboard.press('p');
        //delay(200);
        //Keyboard.releaseAll();     
    } else {
      switch (button_k5) {
        case 1:
          //Serial.println("UP");
          Joystick.setHatSwitch(0, 0);
          break;
        case 2:
          // Serial.println("DOWN");
          Joystick.setHatSwitch(0, 180);
          break;
        case 0:
          // Serial.println("LEFT");
          Joystick.setHatSwitch(0, 270);
          break;
        case 3:
          // Serial.println("RIGHT");
          Joystick.setHatSwitch(0, 90);
          break;
        default:
          break;
      }
      //delay(500);
      //releaseHatSwitch();    
    }   
  } else {
    releaseHatSwitch();
    Joystick.setButton(SW5_JOYBUT, false);
  }
}
