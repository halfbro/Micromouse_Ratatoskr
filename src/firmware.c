#include <avr/interrupt.h>

#include "pathfind.h"
#include "selftest.h"

Maze maze;

int main(void) {
  sei();
  for (;;) {
    performSelfTest();
  }
  return 4;
}
