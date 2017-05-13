#include <stdlib.h>
#include <math.h>
#include <util/delay.h>

#include "buttons.h"
#include "dotmatrix.h"
#include "irsensors.h"
#include "leds.h"
#include "pathfind.h"
#include "motordriver.h"
#include "selftest.h"
#include "systeminit.h"

Maze maze;

int main(void) {
  sysinit();

start:
  performSelfTest();

  while(!buttonIsPressed(BUTTON_LEFT));
  _delay_ms(1000);

  motorsEngage();

  int16_t leftmotorout = 0;
  int16_t rightmotorout = 0;
  IRSensorData initial = {
    .left = 0,
    .leftcenter = 0,
    .rightcenter = 0,
    .right = 0
  };
  readIRSensors(&initial);
  //const int16_t leftsensorhome = initial.left;
  const int16_t leftsensorhome = 700;
  //const int16_t rightsensorhome = initial.right;
  const int16_t rightsensorhome = 700;
  const int16_t wallthreshold = 300;

#define RINGBUF_SIZE 8
  int16_t olddisp[RINGBUF_SIZE];
  int head = 0;

  for (;;) {

    IRSensorData ir = {
      .left = 0,
      .leftcenter = 0,
      .rightcenter = 0,
      .right = 0
    };

    readIRSensors(&ir);

    int16_t leftmotortarget  = 8000;
    int16_t rightmotortarget = 8000;


    if ( leftmotorout < leftmotortarget) {
      leftmotorout += 30;
      if (leftmotorout > leftmotortarget) leftmotorout = leftmotortarget;
    } else if ( leftmotorout > leftmotortarget) {
      leftmotorout -= 30;
      if (leftmotorout < leftmotortarget) leftmotorout = leftmotortarget;
    }

    if ( rightmotorout < rightmotortarget) {
      rightmotorout += 100;
      if (rightmotorout > rightmotortarget) rightmotorout = rightmotortarget;
    } else if ( rightmotorout > rightmotortarget) {
      rightmotorout -= 100;
      if (rightmotorout < rightmotortarget) rightmotorout = rightmotortarget;
    }

    setMotorSpeeds( (int16_t) leftmotorout, (int16_t) rightmotorout);

    _delay_ms(1);  
    if (buttonIsPressed(BUTTON_LEFT)) break;
  }
  motorsDisengage();
  goto start;
}
