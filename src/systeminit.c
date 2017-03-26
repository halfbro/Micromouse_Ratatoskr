#include <avr/interrupt.h>

#include "dotmatrix.h"
#include "motordriver.h"
#include "irsensors.h"
#include "systeminit.h"

void sysinit() {
  initDisplay();
  initMotors();
  initIRSensors();

  // Enable interrupts globally
  sei();
}
