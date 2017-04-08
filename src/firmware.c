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

    int16_t speedX = 0;
    int16_t center = (ir.leftcenter + ir.rightcenter) / 2;
    if (center < 400) {
      speedX = 1200;
    } else {
      speedX = (700 - center)*4;
      if (center > 740 && center < 760) {
        if (ir.right < wallthreshold) {
          setMotorSpeeds(1000,-1000);
          _delay_ms(300);
        }
        if (ir.left < wallthreshold) {
          setMotorSpeeds(-1000,1000);
          _delay_ms(300);
        }
      }
    }

    int16_t leftdisp = ir.left > wallthreshold ? ir.left - leftsensorhome + 300 : 0;
    int16_t rightdisp = ir.right > wallthreshold ? ir.right - rightsensorhome + 100 : 0;
    int16_t disp = (rightdisp - leftdisp)/2;
    olddisp[head++] = disp;
    head = head % RINGBUF_SIZE;

    int16_t vel = olddisp[ (head-1) % RINGBUF_SIZE ]-olddisp[(head)];

    int16_t speedW = -disp - vel * abs(disp);

    if (ir.left > 880) speedW += 1800;
    if (ir.right > 880) speedW -= 1500;

    int16_t leftmotortarget  = speedX + speedW/7;
    int16_t rightmotortarget = speedX - speedW/7;


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
