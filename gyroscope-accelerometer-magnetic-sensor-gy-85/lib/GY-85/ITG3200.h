#include "Arduino.h"
#include "I2CHelper.h"

#ifndef ITG3200_h
#define ITG3200_h

class ITG3200 {
  public:
    ITG3200();
    void init();
    void readGyroscope(int *outGyroXYZ);
    
  private:
    I2CHelper _i2CHelper;
};



#endif
