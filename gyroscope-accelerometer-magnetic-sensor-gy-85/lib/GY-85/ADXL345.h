#include "Arduino.h"
#include "I2CHelper.h"

#ifndef ADXL345_h
#define ADXL345_h

class ADXL345 {
  public: 
    ADXL345();
    void init();
    void readAccelerometer(int *outXYZ);
    void setGRange(int valueToSet);
    void getGRange(byte* rangeSetting);
    void writeToRegister(byte address, byte value);
    void readFromRegister(byte registerAddress, int numOfBytes, byte _buffForDataBytes[]);

	private:
		I2CHelper _i2CHelper;  
};

#endif
