#include "Arduino.h"

#ifndef I2CHelper_h
#define I2CHelper_h

class I2CHelper {
  public: 
    I2CHelper(uint8_t i2cAddress);
    void writeToRegister(byte address, byte value);
    void readFromRegister(byte registerAddress, int numOfBytes, byte _buffForDataBytes[]);

  private:
    uint8_t _deviceI2CAddress;
};

#endif
