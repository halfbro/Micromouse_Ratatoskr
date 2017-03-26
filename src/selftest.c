#include <avr/io.h>
#include <inttypes.h>
#include <stdlib.h>
#include <util/delay.h>

#include "dotmatrix.h"
#include "irsensors.h"
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

void checkIRSensors() {
  _delay_ms(500);

  while (!(PINB & 0b00010000)) {

    // Read sensors into an IRSensorData struct
    IRSensorData sensors = {
      .left = 0,
      .leftcenter = 0,
      .rightcenter = 0,
      .right = 0
    };

    readIRSensors(&sensors);

    char strout[10] = "asdf";
    // Converts int to a string value
    utoa(sensors.right, strout, 10);

    // Output sensor value on the display
    displayString(strout);

    _delay_ms(50);
  }
}

void performSelfTest() {
  checkDisplay();
  runTest(checkLEDs, "LEDs");
  runTest(checkBuzzer, "Buzz");
  runTest(checkIRSensors, "Sens");
  runTest(checkMotors, "Mtrs");
}
