#ifndef __ENCODERS_H__
#define __ENCODERS_H__

#include <inttypes.h>

// Units of measure are 1000ths of a cm (100th of a mm)
#define WHEEL_DIAMETER_CM1000 4445 
#define WHEEL_CIRCUMFERENCE_1000CM 13964

#define MOTOR_GEAR_RATIO_10 9.96
#define TICKS_PER_ROTATION 12
#define TICKS_PER_OUTPUT_ROTATION 119.52

// Circumference/TICKS_PER_OUTPUT_ROTATION (Actual is 0.116834 cm/tick)
#define CM1000_PER_TICK 117

int16_t getLeftEncoderTicks();
int16_t getRightEncoderTicks();

#endif
