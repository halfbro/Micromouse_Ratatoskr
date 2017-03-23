#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <stdlib.h>

#include "motordriver.h"

enum m_Direction {
  DIR_FORWARD=0,
  DIR_REVERSE=1
};

enum m_Direction leftmotordir, rightmotordir;
int16_t leftmotorpower, rightmotorpower;

void initMotors() {

  DDRA |= 0b00001111;

  // Setting up Timer1
  // Use Fast PWM Mode using ICR1 as top value
  TCCR1A = 0b00000010;

  // Set Prescaler to F_CPU/8
  TCCR1B = 0b00011010;

  // Do not use Force Output Compare bits
  TCCR1C = 0b00000000;

  // Set the top value to 10,000
  ICR1 = 10000;

  // Set initial compare value to 0
  OCR1A = 0;
  OCR1B = 0;

  // Disable interrupt to update output pins, to enable use motorsEngage()
  TIMSK1 = 0b00000000;
}

void motorsDisengage() {
  // Disable interrupts on timer
  TIMSK1 &= ~(0b00000111);

  // Set all outputs to 0 (coast)
  PORTA &= ~(0b00001111);
}

void motorsEngage() {
  // Set all outputs to 1 (brake)
  PORTA |= 0b00001111;

  // Reset Timer and reenable interrupts
  TCNT1 = 0;
  TIMSK1 |= 0b00000111;
}

void setMotorSpeeds(int16_t leftpower, int16_t rightpower) {
  leftmotordir = leftpower < 0 ? DIR_REVERSE : DIR_FORWARD;
  rightmotordir = rightpower < 0 ? DIR_REVERSE : DIR_FORWARD;

  int16_t absleftpower = abs(leftpower);
  if (absleftpower > 10000) absleftpower = 10000;
  OCR1A = 10000 - absleftpower;

  int16_t absrightpower = abs(rightpower);
  if (absrightpower > 10000) absrightpower = 10000;
  OCR1B = 10000 - absrightpower;
}

// Define interrupt functions here
// All interrupts are blocking interrupts (ISR_BLOCK)
ISR (TIMER1_COMPA_vect, ISR_BLOCK) {
  if (leftmotordir == DIR_FORWARD) {
    PORTA &= ~(0b00000010);
  } else {
    PORTA &= ~(0b00000001);
  }
}

ISR (TIMER1_COMPB_vect, ISR_BLOCK) {
  if (rightmotordir == DIR_FORWARD) {
    PORTA &= ~(0b00000100);
  } else {
    PORTA &= ~(0b00001000);
  }
}

ISR (TIMER1_OVF_vect, ISR_BLOCK) {
  PORTA |= 0b00001111;
}
