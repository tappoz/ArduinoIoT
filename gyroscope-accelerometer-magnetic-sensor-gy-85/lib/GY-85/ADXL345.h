#include "Arduino.h"
#include "I2CHelper.h"

#ifndef ADXL345_h
#define ADXL345_h

class ADXL345 {
  public: 
    ADXL345();
    void init();
    void readAccelerometer(float *accXYZ);
    
  private:
    I2CHelper _i2CHelper;
    int mapToRegisterGValue(int gHalfRange);
    void readRawAccelerometer(int *rawAccXYZ);
};

#endif
