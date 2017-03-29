#include <avr/io.h>
#include <inttypes.h>

#include "leds.h"

void initLEDs() {
  DDRA |= 0b11000000;
  DDRB |= 0b00000011;
}

void ledsOn(uint8_t mask) {
  PORTA |= (mask & 0b0011) << 6;
  PORTB |= (mask & 0b1100) >> 2;
}

void ledsOff(uint8_t mask) {
  PORTA &= ~((mask & 0b0011) << 6);
  PORTB &= ~((mask & 0b1100) >> 2);
}

void ledsOnlyOn(uint8_t mask) {
  ledsOn(mask);
  ledsOff(~mask);
}
