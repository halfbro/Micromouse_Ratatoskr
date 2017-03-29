#include <avr/io.h>
#include <inttypes.h>

#include "buttons.h"

int buttonIsPressed(uint8_t mask) {
  return ( ((mask << 2) & PINB) > 0 ) ? 1 : 0;
}
