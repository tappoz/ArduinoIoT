#include "Arduino.h"
#include "I2CHelper.h"

#ifndef HMC5883L_h
#define HMC5883L_h

class HMC5883L {
  public:
    HMC5883L();
    void init();
    void readMagnetometer(float *outXYZ);
    float convertToHorizontalYawHeading(float *outXYZ);
  
  private:
    I2CHelper _i2CHelper;
};


#endif

