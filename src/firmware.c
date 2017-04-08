#include <util/delay.h>

#include "buttons.h"
#include "pathfind.h"
#include "motordriver.h"
#include "selftest.h"
#include "systeminit.h"

Maze maze;

int main(void) {
  sysinit();

  while(!buttonIsPressed(BUTTON_LEFT));
  _delay_ms(1000);

  //for (;;) {
  //  performSelfTest();
  //}

  double leftmotortarget = 2000.0;
  double rightmotortarget = 2000.0;

  int16_t leftmotorout = 0;
  int16_t rightmotorout = 0;

  motorsEngage();
  for (;;) {

    if ( leftmotorout < leftmotortarget) {
      leftmotorout += 30;
      if (leftmotorout > leftmotortarget) leftmotorout = leftmotortarget;
    } else if ( leftmotorout > leftmotortarget) {
      leftmotorout -= 30;
      if (leftmotorout < leftmotortarget) leftmotorout = leftmotortarget;
    }

    if ( rightmotorout < rightmotortarget) {
      rightmotorout += 30;
      if (rightmotorout > rightmotortarget) rightmotorout = rightmotortarget;
    } else if ( rightmotorout > rightmotortarget) {
      rightmotorout -= 30;
      if (rightmotorout < rightmotortarget) rightmotorout = rightmotortarget;
    }

    setMotorSpeeds( (int16_t) leftmotorout, (int16_t) rightmotorout);

    _delay_ms(1);  
  }
}
