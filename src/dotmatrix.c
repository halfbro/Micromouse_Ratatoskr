#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include "dotmatrix.h"

void initDisplay() {
  DDRC = 0b01111111;
  DDRD = 0b11111111;
  
  PORTD = 0b00101111;
}

void clearDisplay() {
  PORTD = 0b00001111;
  PORTD = 0b00101111;
}

void displayChar(uint8_t c, int pos) {
  PORTD &= 0b11111000;
  switch (pos) {
    case 0: PORTD |= 0b00000011; break;
    case 1: PORTD |= 0b00000001; break;
    case 2: PORTD |= 0b00000010; break;
    case 3: PORTD |= 0b00000000; break;
  }
  PORTC = c;
  PORTD |= 0b00000100;
}

void displayString(char *s) {
  for (int i=0; i<4; ++i) {
    if (s[i] == '\0')
      displayChar(' ', i);
    else
      displayChar(s[i], i);
    _delay_us(1);
  }
}
