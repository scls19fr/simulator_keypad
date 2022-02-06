#include <ezAnalogKeypad.h>
#include <Keyboard.h>

#define PIN_ANALOG_KEYPAD_4x4 A0

ezAnalogKeypad keypad_4x4(PIN_ANALOG_KEYPAD_4x4);

void setup() {
  Serial.begin(9600);

  keypad_4x4.setNoPressValue(0);  // analog value when no key is pressed
  keypad_4x4.registerKey('1', 1023);  // but=01 : row=1,col=1
  keypad_4x4.registerKey('2', 930);   // but=02 : row=1,col=2
  keypad_4x4.registerKey('3', 852);   // but=03 : row=1,col=3
  keypad_4x4.registerKey('4', 786);   // but=04 : row=1,col=4
  keypad_4x4.registerKey('5', 675);   // but=05 : row=2,col=1
  keypad_4x4.registerKey('6', 632);   // but=06 : row=2,col=2
  keypad_4x4.registerKey('7', 596);   // but=07 : row=2,col=3
  keypad_4x4.registerKey('8', 563);   // but=08 : row=2,col=4
  keypad_4x4.registerKey('9', 502);   // but=09 : row=3,col=1
  keypad_4x4.registerKey('a', 478);   // but=10 : row=3,col=2
  keypad_4x4.registerKey('b', 457);   // but=11 : row=3,col=3
  keypad_4x4.registerKey('c', 437);   // but=12 : row=3,col=4
  keypad_4x4.registerKey('d', 400);   // but=13 : row=4,col=1
  keypad_4x4.registerKey('e', 321);   // but=14 : row=4,col=2
  keypad_4x4.registerKey('f', 269);   // but=15 : row=4,col=3
  keypad_4x4.registerKey('0', 231);   // but=16 : row=4,col=4

  Keyboard.begin();
}

void loop() {
  //Serial.println(analogRead(PIN_ANALOG_KEYPAD_4x4));
  unsigned char button_4x4 = keypad_4x4.getKey();
  if (button_4x4) {
    // Serial.print("The button ");
    // Serial.print((int)button_4x4);
    // Serial.println(" is pressed");
    switch (button_4x4) {
      case '1':
        Keyboard.press('g');
        break;
      case '2':
        Keyboard.press('h');
        break;
      case '3':
        Keyboard.press('j');
        break;
      case '4':
        Keyboard.press('q');  // a=azerty -> q=qwerty
        break;
      case '5':
        Keyboard.press(KEY_F1);
        break;
      case '6':
        Keyboard.press(KEY_F2);
        break;
      case '7':
        Keyboard.press(KEY_F3);
        break;
      case '8':
        Keyboard.press(KEY_F4);
        break;
      case '9':
        Keyboard.press(KEY_END);
        break;
      case 'a':
        Keyboard.press(KEY_HOME);
        break;
      case 'b':
        Keyboard.press(KEY_F5);
        break;
      case 'c':
        Keyboard.press(KEY_F6);
        break;
      case 'd':
        Keyboard.press(KEY_PAGE_DOWN);
        break;
      case 'e':
        Keyboard.press(KEY_PAGE_UP);
        break;
      case 'f':
        Keyboard.press('m');  // ,=azerty -> m=qwerty
        break;
      case '0':
        Keyboard.press('y');
        break;
      default:
        break;
    }
    delay(100);
    Keyboard.releaseAll();
  }
  delay(100);
}
