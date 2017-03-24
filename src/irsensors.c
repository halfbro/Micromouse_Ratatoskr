#include <avr/io.h>
#include <inttypes.h>

#include "irsensors.h"

uint16_t readADC(uint8_t sensornum) {
  // Select the correct ADC output (must be from 0-3)
  sensornum &= 0b00000011;
  ADMUX &= ~(0b00000111);
  ADMUX |= sensornum;

  // Start the conversion process
  ADCSRA |= 0b010000000;

  // Wait for the conversion to finish (ADCSRA will go low to 0)
  while (ADCSRA & 0b01000000);

  return ADC;
}

void initIRSensors() {
  // Initialize ADC to use AREF as the analog reference and select the first ADC
  ADMUX = 0b00000000;

  // Enable the ADC and set ADC prescaler to 32 (option 4)
  ADCSRA = 0b10010100;

  // Set the IR Emitters as outputs
  //DDRF? |= 0b00001111 ?;
}

void readIRSensors(IRSensorData* sensors) {
  uint16_t templ, templc, temprc, tempr;
  // Need to add the emitter pulsing somewhere in here...
  templ = readADC(0);
  templc = readADC(1);
  temprc = readADC(2);
  tempr = readADC(3);
  sensors->left = templ;
  sensors->leftcenter = templc;
  sensors->rightcenter = temprc;
  sensors->right = tempr;
}
