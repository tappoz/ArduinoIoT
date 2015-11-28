// Cfr.:
// http://www.himix.lt/arduino/arduino-and-gy-85-9dof-accelerometer-adxl345-gyroscope-itg3200-and-magnetometer-hmc5883-angle-information-comparison/
// http://eeenthusiast.com/arduino-i2c-adxl-345-robot/
// https://github.com/sqrtmo/GY-85-arduino/blob/master/GY_85.cpp

#include <Wire.h>
#include <SPI.h>
#include "I2CHelper.h"
#include "ADXL345.h"
#include "ITG3200.h"
#include "HMC5883L.h"
#include "GY85.h"

// milliseconds between reads
const int DEVICE_SAMPLING_MS = 2000;

ADXL345 accelerometer;
ITG3200 gyroscope;
HMC5883L magnetometer;

GY85 inertialMeasurementUnit;

void setup(){
  Serial.begin(9600);
  inertialMeasurementUnit.init();
}

void loop(){

  String dataRow = inertialMeasurementUnit.getFormattedDataRow();
  Serial.println(dataRow);

  delay(DEVICE_SAMPLING_MS);
}
