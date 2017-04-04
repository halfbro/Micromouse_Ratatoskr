#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#include "atmega-adc.h"
#include "dotmatrix.h"
#include "irsensors.h"

void initIRSensors() {
  // Set IR Emitters as outputs
  DDRE |= 0b00000011;
  DIDR0 = 0b11111111;
}

uint16_t readADC(uint8_t sensornum) {
  return adc_read(ADC_PRESCALER_128, ADC_VREF_AREF, sensornum);
}

void readIRSensors(IRSensorData *sensors) {
  uint16_t templ  = 0;
  uint16_t templc = 0;
  uint16_t temprc = 0;
  uint16_t tempr  = 0;

  PORTE |= 0b00000010;

  _delay_us(200);

  templ = readADC(0);

  _delay_us(200);

  templc = readADC(1);

  PORTE &= ~(0b00000010);
  _delay_us(200);
  PORTE |= 0b00000001;
  _delay_us(200);

  temprc = readADC(2);

  _delay_us(200);

  tempr = readADC(3);

  PORTE &= ~(0b00000001);
  sensors->left = templ;
  sensors->leftcenter = templc;
  sensors->rightcenter = temprc;
  sensors->right = tempr;
}
