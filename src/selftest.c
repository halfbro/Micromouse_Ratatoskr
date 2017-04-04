#include <avr/io.h>
#include <inttypes.h>
#include <stdlib.h>
#include <util/delay.h>

#include "buttons.h"
#include "dotmatrix.h"
#include "irsensors.h"
#include "leds.h"
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
  int t = 0;
  while (!buttonIsPressed(BUTTON_RIGHT)) {
    if (t<500) {
      ledsOn (LED_LEFT  | LED_CENTER_LEFT );
      ledsOff(LED_RIGHT | LED_CENTER_RIGHT);
    } else {
      ledsOn (LED_RIGHT | LED_CENTER_RIGHT);
      ledsOff(LED_LEFT  | LED_CENTER_LEFT );
    }

    _delay_ms(1);
    t++;
    if (t>1000) t=0;
  }

  ledsOnlyOn( LED_NONE );
}

void checkDisplay() {
  displayString("Test");

  _delay_ms(200);
  while (!buttonIsPressed(BUTTON_RIGHT));

  clearDisplay();
}

void checkBuzzer() {
  DDRB |= 0b00100000;

  while (!buttonIsPressed(BUTTON_RIGHT)) {
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

  int sensorchoice = 0;

  while (!buttonIsPressed(BUTTON_RIGHT)) {

    // Read sensors into an IRSensorData struct
    IRSensorData sensors = {
      .left = 0,
      .leftcenter = 0,
      .rightcenter = 0,
      .right = 0
    };

    readIRSensors(&sensors);

    uint16_t sensorval = 0;

    switch (sensorchoice) {
      case 0: sensorval = sensors.left; ledsOnlyOn(LED_LEFT); break;
      case 1: sensorval = sensors.leftcenter; ledsOnlyOn(LED_CENTER_LEFT); break;
      case 2: sensorval = sensors.rightcenter; ledsOnlyOn(LED_CENTER_RIGHT); break;
      case 3: sensorval = sensors.right; ledsOnlyOn(LED_RIGHT); break;
    }

    char strout[5] = "\0\0\0\0";
    // Converts int to a string value
    utoa(sensorval, strout, 10);

    // Output sensor value on the display
    displayString(strout);

    if (buttonIsPressed(BUTTON_CENTER)) {
      sensorchoice += 1;
      if (sensorchoice > 3) sensorchoice = 0;
      char name[5] = "Senx";
      name[3] = sensorchoice + 1 + 0x30;
      displayString(name);
      _delay_ms(500);
    }

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
