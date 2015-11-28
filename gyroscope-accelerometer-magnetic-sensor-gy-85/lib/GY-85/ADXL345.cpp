#include "Arduino.h"
#include <SPI.h>
#include "I2CHelper.h"
#include "ADXL345.h"

// ADXL345 accelerometer I2C address as specified in data sheet
// http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf
// 
// X-axis rotation: roll, 
// Y-axis rotation: pitch, 
// Z-axis rotation: yaw, (an 3-axis accelerometer can not measure it, as the force vector of gravity does not change during the movement).
#define ADXL345_I2C (0x53)

// register cells
#define D0 1  // 2^0 0x01
#define D1 2  // 2^1 0x02
#define D2 4  // 2^2 0x04
#define D3 8  // 2^3 0x08
#define D4 16 // 2^4 0x10
#define D5 32 // 2^5 0x20
#define D6 64 // 2^6 0x40

#define DATAX0 0x32 // X-Axis Data 0
// #define DATAX1 0x33 // X-Axis Data 1
// #define DATAY0 0x34 // Y-Axis Data 0
// #define DATAY1 0x35 // Y-Axis Data 1
// #define DATAZ0 0x36 // Z-Axis Data 0
// #define DATAZ1 0x37 // Z-Axis Data 1

#define POWER_CTL (0x2D)
#define DATA_FORMAT (0x31)

int gHalfRangeToBeUsed;
float sensorGScalingFactor;

ADXL345::ADXL345():_i2CHelper(ADXL345_I2C){}

// As per datasheet, the gravity G is like:
//   2 meaning half of the range +/- 2g
//   4 meaning half of the range +/- 4g
// and so on...
int ADXL345::mapToRegisterGValue(int gHalfRange) {
  int registerGValue;
  
  switch (gHalfRange) {
    case 2:  
      registerGValue = 0x00; 
      break;
    case 4:  
      registerGValue = 0x01; 
      break;
    case 8:  
      registerGValue = 0x10; 
      break;
    case 16: 
      registerGValue = 0x11; 
      break;
    default: 
      registerGValue = 0x00;
  }

  Serial.print("gHalfRange: ");
  Serial.print(String(gHalfRange));
  Serial.print(" registerGValue: ");
  Serial.println(String(registerGValue));

  return registerGValue;
}

void ADXL345::init() {
  // clear the POWER_CTL register
  _i2CHelper.writeToRegister(POWER_CTL, D0);
  // POWER_CTL D4 register high to make sure it is not in sleep mode
  _i2CHelper.writeToRegister(POWER_CTL, D4);
  // POWER_CTL D3 register high to set the module into measure mode
  _i2CHelper.writeToRegister(POWER_CTL, D3);

  // gravity G: +/- 4g range
  gHalfRangeToBeUsed = 4;

  // the sensor maps the signal into 10 bits
  // if we set the measurment +/-4g (gravity) range then the gravity 
  // in Gs (unit of measurement for gravity) is:
  // Gs = value from the sensor * (G-range/(2^10)) 
  // in other words having a range of 4g+4g=8g:
  // Gs = value from the sensor * (8/1024)
  sensorGScalingFactor = (float)(gHalfRangeToBeUsed + gHalfRangeToBeUsed) / (float) 1024;
  Serial.print("Scale factor: ");
  Serial.println(String(sensorGScalingFactor, 4));


  // DATA_FORMAT register to set the g range (gravity) into +/- 4g range
  _i2CHelper.writeToRegister(DATA_FORMAT, mapToRegisterGValue(gHalfRangeToBeUsed));
}

void ADXL345::readRawAccelerometer(int *rawAccXYZ) {
  byte accelerometerValues[6];
  // the output data is twos complement, 
  // with DATAx0 as the least significant byte and DATAx1 as the most significant byte,
  // where x represent X, Y,  or Z
  _i2CHelper.readFromRegister(DATAX0, 6, accelerometerValues);

  rawAccXYZ[0] = ((int)accelerometerValues[1]) << 8 | (int)accelerometerValues[0]; 
  rawAccXYZ[1] = ((int)accelerometerValues[3]) << 8 | (int)accelerometerValues[2]; 
  rawAccXYZ[2] = ((int)accelerometerValues[5]) << 8 | (int)accelerometerValues[4];
}

void ADXL345::readAccelerometer(float *outXYZ) {
  int rawAccXYZ[3];
  readRawAccelerometer(rawAccXYZ);

  outXYZ[0] = (float) rawAccXYZ[0] * sensorGScalingFactor;
  outXYZ[1] = (float) rawAccXYZ[1] * sensorGScalingFactor;
  outXYZ[2] = (float) rawAccXYZ[2] * sensorGScalingFactor;
}
