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
  uint16_t templ, templc, temprc, tempr;

  PORTE |= 0b00000001;
  _delay_us(100);
  templ = readADC(1);
  _delay_us(100);
  templc = readADC(1);
  PORTE &= ~(0b00000001);

  _delay_us(100);

  PORTE |= 0b00000010;
  _delay_us(100);
  temprc = readADC(1);
  _delay_us(100);
  tempr = readADC(1);
  PORTE &= ~(0b00000010);

  sensors->left = templ;
  sensors->leftcenter = templc;
  sensors->rightcenter = temprc;
  sensors->right = tempr;
}
