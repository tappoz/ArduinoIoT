#include "Arduino.h"
#include <SPI.h>
#include "I2CHelper.h"
#include "ADXL345.h"

// ADXL345 accelerometer I2C address as specified in data sheet
// http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf
#define ADXL345_I2C (0x53)

// register cells
#define D0 1  // 2^0
// #define D1 2  // 2^1
// #define D2 4  // 2^2
// #define D3 8  // 2^3
// #define D4 16 // 2^4
// #define D5 32 // 2^5
// #define D6 64 // 2^6

#define DATAX0 0x32 // X-Axis Data 0
// #define DATAX1 0x33 // X-Axis Data 1
// #define DATAY0 0x34 // Y-Axis Data 0
// #define DATAY1 0x35 // Y-Axis Data 1
// #define DATAZ0 0x36 // Z-Axis Data 0
// #define DATAZ1 0x37 // Z-Axis Data 1

#define POWER_CTL (0x2D)
#define DATA_FORMAT (0x31)

ADXL345::ADXL345():_i2CHelper(ADXL345_I2C){}

void ADXL345::writeToRegister(byte address, byte value) {
  _i2CHelper.writeToRegister(address, value);
}

void ADXL345::readFromRegister(byte registerAddress, int numOfBytes, byte _buffForDataBytes[]) {
  _i2CHelper.readFromRegister(registerAddress, numOfBytes, _buffForDataBytes);
}
