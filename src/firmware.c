#include "pathfind.h"
#include "selftest.h"
#include "systeminit.h"

Maze maze;

int main(void) {
  sysinit();
  for (;;) {
    performSelfTest();
  }
  return 4;
}
