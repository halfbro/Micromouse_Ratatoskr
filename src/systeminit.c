#include <avr/interrupt.h>

#include "dotmatrix.h"
#include "motordriver.h"
#include "systeminit.h"

void sysinit() {
  initDisplay();
  initMotors();

  // Enable interrupts globally
  sei();
}
