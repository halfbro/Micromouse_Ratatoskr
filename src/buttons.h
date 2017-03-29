#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include <inttypes.h>

#define BUTTON_LEFT   1
#define BUTTON_CENTER 2
#define BUTTON_RIGHT  4

int buttonIsPressed(uint8_t mask);

#endif
