#include "Arduino.h"
#include "I2CHelper.h"
#include "HMC5883L.h"

// Honeywell HMC5883L magnetometer
// https://www.adafruit.com/datasheets/HMC5883L_3-Axis_Digital_Compass_IC.pdf
#define HMC5883L_I2C 0x1E
#define MODE_REGISTER 0x02

#define DATA_OUTPUT_X_REGISTER_A_MSB 0x03
// #define DATA_OUTPUT_X_REGISTER_B_LSB 0x04
// #define DATA_OUTPUT_Y_REGISTER_A_MSB 0x05
// #define DATA_OUTPUT_Y_REGISTER_B_LSB 0x06
// #define DATA_OUTPUT_Z_REGISTER_A_MSB 0x07
// #define DATA_OUTPUT_Z_REGISTER_B_LSB 0x08

HMC5883L::HMC5883L():_i2CHelper(HMC5883L_I2C){}

void HMC5883L::init() {
  // set mode register to continuous measurement mode
  _i2CHelper.writeToRegister(MODE_REGISTER, 0x00);
}

void HMC5883L::readMagnetometer(int *outXYZ) {
  byte magnetometerValues[6];
  // the output data is twos complement, 
  // with DATA_OUTPUT_X_REGISTER_A_MSB / DATA_OUTPUT_X_REGISTER_B_LSB 
  // for most/least significant bytes, repeated for X, Y, Z 
  // increasing by 1 the register address 
  _i2CHelper.readFromRegister(DATA_OUTPUT_X_REGISTER_A_MSB, 6, magnetometerValues);

  outXYZ[0] = (((int)magnetometerValues[0]) << 8) | magnetometerValues[1]; 
  outXYZ[1] = (((int)magnetometerValues[2]) << 8) | magnetometerValues[3]; 
  outXYZ[2] = (((int)magnetometerValues[4]) << 8) | magnetometerValues[5];

}



