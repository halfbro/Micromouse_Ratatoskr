#include <util/delay.h>
#include <string.h>
#include "dotmatrix.h"

#include "encoders.h"
#include "i2csoft.h"

uint8_t i2cReadByte(uint8_t address, uint8_t reg) {

  SoftI2CStart();
  //SoftI2CWriteByte(address << 1 | 0);
  //SoftI2CWriteByte(reg);
  //SoftI2CStop();
  //SoftI2CStart();
  SoftI2CWriteByte(address << 1 | 1);
  uint8_t ret = SoftI2CReadByte(0);
  SoftI2CStop();

  return (uint8_t) ret;
}

int16_t getLeftEncoderTicks() {
  uint8_t high, low;
  high = i2cReadByte(0x3E, 0);
  low  = i2cReadByte(0x3E, 1);
  return (high << 8 | low);
}

int16_t getRightEncoderTicks() {
  uint8_t high, low;
  high = i2cReadByte(0x3D, 0);
  low  = i2cReadByte(0x3D, 1);
  return (high << 8 | low);
}
