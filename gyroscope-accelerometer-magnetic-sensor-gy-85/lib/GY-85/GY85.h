#include "Arduino.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "HMC5883L.h"

#ifndef GY85_h
#define GY85_h

class GY85 {

  public:
    GY85();
    // void init();
    void heading(String &headingStr);
  private:
    ADXL345 _accelerometer;
    ITG3200 _gyroscope;
    HMC5883L _magnetometer;
};

#endif
