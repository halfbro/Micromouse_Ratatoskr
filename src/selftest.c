#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>

#include "dotmatrix.h"
#include "motordriver.h"
#include "selftest.h"

typedef void (*TestFunc)(void);

void runTest(TestFunc test, char *name) {
  displayString(name);
  _delay_ms(200);
  test();
  clearDisplay();
}

void checkLEDs() {
  DDRA |= 0b11000000;
  DDRB |= 0b00000011;

  int t = 0;
  while (!(PINB & 0b00010000)) {
    if (t<500) {
      PORTA |=   0b11000000;
      PORTB &= ~(0b00000011);
    } else {
      PORTA &= ~(0b11000000);
      PORTB |=   0b00000011;
    }

    _delay_ms(1);
    t++;
    if (t>1000) t=0;
  }
  PORTA &= ~(0b11000000);
  PORTB &= ~(0b00000011);
}

void checkDisplay() {
  displayString("Test");

  _delay_ms(200);
  while (!(PINB & 0b00010000));

  clearDisplay();
}

void checkBuzzer() {
  DDRB |= 0b00100000;

  while (!(PINB & 0b00010000)) {
    PORTB ^= 0b00100000;
    _delay_us(250);
  }
}

void checkMotors() {
  initMotors();
  motorsEngage();
  setMotorSpeeds(500, 0);
  _delay_ms(1000);
  setMotorSpeeds(-500, 0);
  _delay_ms(1000);
  setMotorSpeeds(0, 500);
  _delay_ms(1000);
  setMotorSpeeds(0, -500);
  _delay_ms(1000);
  setMotorSpeeds(0, 0);
  _delay_ms(1000);
  motorsDisengage();
}

void performSelfTest() {
  initDisplay();
  checkDisplay();
  runTest(checkLEDs, "LEDs");
  runTest(checkBuzzer, "Buzz");
  runTest(checkMotors, "Mtrs");
}
