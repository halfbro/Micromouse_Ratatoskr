#ifndef __LEDS_H__
#define __LEDS_H__

#define LED_NONE          0
#define LED_LEFT          1
#define LED_CENTER_LEFT   2
#define LED_CENTER_RIGHT  4
#define LED_RIGHT         8
#define LED_ALL           15

void initLEDs();

void ledsOn(uint8_t mask);
void ledsOff(uint8_t mask);

void ledsOnlyOn(uint8_t mask);

#endif

