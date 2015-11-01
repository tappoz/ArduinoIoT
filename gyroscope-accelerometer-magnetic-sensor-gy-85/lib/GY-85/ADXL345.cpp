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
#define D0 1  // 2^0
#define D1 2  // 2^1
#define D2 4  // 2^2
#define D3 8  // 2^3
#define D4 16 // 2^4
#define D5 32 // 2^5
#define D6 64 // 2^6

#define DATAX0 0x32 // X-Axis Data 0
// #define DATAX1 0x33 // X-Axis Data 1
// #define DATAY0 0x34 // Y-Axis Data 0
// #define DATAY1 0x35 // Y-Axis Data 1
// #define DATAZ0 0x36 // Z-Axis Data 0
// #define DATAZ1 0x37 // Z-Axis Data 1

#define POWER_CTL (0x2D)
#define DATA_FORMAT (0x31)

ADXL345::ADXL345():_i2CHelper(ADXL345_I2C){}

void ADXL345::init() {
  // clear the POWER_CTL register
  _i2CHelper.writeToRegister(POWER_CTL, D0);
  // POWER_CTL D4 register high to make sure it is not in sleep mode
  _i2CHelper.writeToRegister(POWER_CTL, D4);
  // POWER_CTL D3 register high to set the module into measure mode
  _i2CHelper.writeToRegister(POWER_CTL, D3);
  // DATA_FORMAT register to set the g range (gravity)
  this->setGRange(4);
}

void ADXL345::readAccelerometer(int *outXYZ) {
  byte accelerometerValues[6];
  // the output data is twos complement, 
  // with DATAx0 as the least significant byte and DATAx1 as the most significant byte,
  // where x represent X, Y,  or Z
  _i2CHelper.readFromRegister(DATAX0, 6, accelerometerValues);

  outXYZ[0] = (((int)accelerometerValues[1]) << 8) | accelerometerValues[0]; 
  outXYZ[1] = (((int)accelerometerValues[3]) << 8) | accelerometerValues[2]; 
  outXYZ[2] = (((int)accelerometerValues[5]) << 8) | accelerometerValues[4];

  delete[] accelerometerValues;
}


// Sets the range setting for g (gravity) changing the DATA_FORMAT register.
// Possible input values are: 2, 4, 8, 16.
// D1 D0 Range     byte
//  0  0 +2/-2   g B00000000
//  0  1 +4/-4   g B00000001
//  1  0 +8/-8   g B00000010
//  1  1 +16/-16 g B00000011
void ADXL345::setGRange(int valueToSet) {
  byte newSetting;
  // byte currentSetting;
  
  switch (valueToSet) {
    case 2:  
      newSetting = B00000000; 
      break;
    case 4:  
      newSetting = B00000001; 
      break;
    case 8:  
      newSetting = B00000010; 
      break;
    case 16: 
      newSetting = B00000011; 
      break;
    default: 
      newSetting = B00000000;
  }
  // readFromRegister(DATA_FORMAT, 1, &currentSetting);
  // newSetting |= (currentSetting & B11101100);
  
  _i2CHelper.writeToRegister(DATA_FORMAT, newSetting);
}

// Gets the g (gravity) range setting and return it into the input rangeSetting
// it can be 2, 4, 8 or 16
void ADXL345::getGRange(byte* rangeSetting) {
  byte _b;
  _i2CHelper.readFromRegister(DATA_FORMAT, 1, &_b);
  *rangeSetting = _b & B00000011;
}
