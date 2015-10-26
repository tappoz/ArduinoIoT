#include "Arduino.h"
#include <Wire.h>
#include "I2CHelper.h"

I2CHelper::I2CHelper() {
  // do nothing in the constructor
}

// writes value to address register on device at i2cAddress
void I2CHelper::writeToRegister(uint8_t i2cAddress, byte address, byte value) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}
