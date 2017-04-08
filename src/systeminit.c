#include <avr/interrupt.h>
#include <stdlib.h>

#include "dotmatrix.h"
#include "leds.h"
#include "motordriver.h"
#include "irsensors.h"
#include "systeminit.h"

void sysinit() {
  initDisplay();
  initMotors();
  initIRSensors();
  IRSensorData s;
  readIRSensors(&s);
  srand(s.left ^ s.right ^ s.leftcenter);
  initLEDs();

  // Enable interrupts globally
  sei();
}
