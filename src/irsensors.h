#ifndef __IRSENSOR_H__
#define __IRSENSOR_H__

#include <inttypes.h>

typedef struct IRData {
  uint16_t left;
  uint16_t leftcenter;
  uint16_t rightcenter;
  uint16_t right;
} IRSensorData;

void initIRSensors();
void readIRSensors(IRSensorData *sensors);

#endif
