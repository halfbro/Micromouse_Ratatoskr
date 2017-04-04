#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#include "atmega-adc.h"
#include "dotmatrix.h"
#include "irsensors.h"

void initIRSensors() {
  // Set IR Emitters as outputs
  DDRE |= 0b00000011;

  DDRF &= ~(0b00001111);
}

uint16_t readADC(uint8_t sensornum) {
  return adc_read(ADC_PRESCALER_128, ADC_VREF_AREF, sensornum);
}

void readIRSensors(IRSensorData *sensors) {

  PORTE |= 0b00000010;
  uint16_t templ  = readADC(0);
  uint16_t templc = readADC(1);
  PORTE &= ~(0b00000010);

  PORTE |= 0b00000001;
  uint16_t temprc = readADC(2);
  uint16_t tempr  = readADC(3);
  PORTE &= ~(0b00000001);

  sensors->left = templ;
  sensors->leftcenter = templc;
  sensors->rightcenter = temprc;
  sensors->right = tempr;
}
