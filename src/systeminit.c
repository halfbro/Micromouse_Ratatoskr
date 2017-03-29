#include <avr/interrupt.h>

#include "dotmatrix.h"
#include "leds.h"
#include "motordriver.h"
#include "irsensors.h"
#include "systeminit.h"

void sysinit() {
  initDisplay();
  initMotors();
  initIRSensors();
  initLEDs();

  // Enable interrupts globally
  sei();
}
