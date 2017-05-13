#include <util/delay.h>

#include "atmega-adc.h"

uint16_t adc_read(uint8_t prescaler, uint8_t vref, uint8_t pin) {
	ADMUX = vref | pin;
	
	ADCSRA = _BV(ADEN) | _BV(ADSC) | prescaler;
	while(!(ADCSRA & _BV(ADIF)));
  _delay_us(400);
	
	return (ADCL | (ADCH<<8));
}
