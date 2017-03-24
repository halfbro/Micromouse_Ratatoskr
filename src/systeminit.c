#include <avr/interrupt.h>

#include "dotmatrix.h"
#include "motordriver.h"
#include "irsensors.h"
#include "systeminit.h"

void sysinit() {
  initDisplay();
  initIRSensors();
  initMotors();

  // Enable interrupts globally
  sei();
}
