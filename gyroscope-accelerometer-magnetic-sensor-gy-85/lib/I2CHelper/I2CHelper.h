#include "Arduino.h"

#ifndef I2CHelper_h
#define I2CHelper_h

class I2CHelper {
  public: 
    I2CHelper();
    void writeToRegister(uint8_t i2cAddress, byte address, byte value);
    void readFromRegister(uint8_t i2cAddress, byte registerAddress, int numOfBytes, byte _buffForDataBytes[]);
};

#endif
