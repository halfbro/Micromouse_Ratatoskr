#define I2C_SLAVE_ADDRESS 0x4 // the 7-bit address (remember to change this when adapting this example)

#include <TinyWireS.h>

#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 8 )
#endif

volatile int16_t numticks = 0;

ISR(PCINT3_vect){
  // The other pin is high
  if (PINB & 0b00010000)
    // And this one is high
    if (PINB & 0b00001000)
      // We are moving forward
      numticks += 1;
    else
      numticks -= 1;
  else
    if (PINB & 0b00001000)
      // We are moving backwards
      numticks -= 1;
    else
      numticks += 1;
}

ISR(PCINT4_vect){
  // The other pin is high
  if (PINB & 0b00001000)
    // And this one is high
    if (PINB & 0b00010000)
      // We are moving backwards
      numticks -= 1;
    else
      numticks += 1;
  else
    if (PINB & 0b00010000)
      // We are moving forward
      numticks += 1;
    else
      numticks -= 1;
}

/**
 * This is called for each read request we receive, never put more than one byte of data (with TinyWireS.send) to the 
 * send-buffer when using this callback
 */
void requestEvent()
{
  // Copy numticks so that the ISR doesn't mess things ups in between sends
  int16_t numticks_cpy = numticks;
  numticks = 0;

  // Always return the MSB, then LSB of the number of ticks since last check
  TinyWireS.send(numticks_cpy >> 8);
  TinyWireS.send(numticks_cpy & 0x00FF);
}

/**
 * The I2C data received -handler
 *
 * This needs to complete before the next incoming transaction (start, data, restart/stop) on the bus does
 * so be quick, set flags for long running tasks to be called from the mainloop instead of running them directly,
 */
void receiveEvent(uint8_t howMany)
{
  if (howMany < 1)
  {
    // Sanity-check
    return;
  }
  if (howMany > TWI_RX_BUFFER_SIZE)
  {
    // Also insane number
    return;
  }
  while(howMany--)
  {
    TinyWireS.receive();
  }

  //numticks = 0;
}

void setup()
{
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onReceive(receiveEvent);
  TinyWireS.onRequest(requestEvent);

  GIMSK = 0b00100000;
  PCMSK = 0b00011000;
  DDRB &= ~(0b00011000);
  sei();
}

void loop()
{
  /**
   * This is the only way we can detect stop condition (http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=984716&sid=82e9dc7299a8243b86cf7969dd41b5b5#984716)
   * it needs to be called in a very tight loop in order not to miss any (REMINDER: Do *not* use delay() anywhere, use tws_delay() instead).
   * It will call the function registered via TinyWireS.onReceive(); if there is data in the buffer on stop.
   */
  TinyWireS_stop_check();
}
