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
    
	private:
    I2CHelper _i2CHelper;
};

#endif
