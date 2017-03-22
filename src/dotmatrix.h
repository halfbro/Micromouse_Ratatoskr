#ifndef __DOTMATRIX_H__
#define __DOTMATRIX_H__

#include <inttypes.h>

void initDisplay();
void clearDisplay();
void displayChar(uint8_t c, int pos);
void displayString(char *s);

#endif
