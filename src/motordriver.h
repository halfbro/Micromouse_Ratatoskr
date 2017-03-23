#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__

#include <inttypes.h>

void initMotors();
void motorsDisengage();
void motorsEngage();
// leftpower and rightpower are on scale from -10000 to 10000
void setMotorSpeeds(int16_t leftpower, int16_t rightpower);

#endif
