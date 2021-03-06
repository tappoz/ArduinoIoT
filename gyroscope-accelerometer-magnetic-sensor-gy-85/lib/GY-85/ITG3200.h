#include "Arduino.h"
#include "I2CHelper.h"

#ifndef ITG3200_h
#define ITG3200_h

class ITG3200 {
  public:
    ITG3200();
    void init();
    void readGyroscope(float *gyroXYZ);
    void readTemperature(float *temperature);

  private:
    I2CHelper _i2CHelper;
    float calibrationOffset[3];
    void readRawGyroscope(int *gyroXYZ);
    void calibrate();
};



#endif
