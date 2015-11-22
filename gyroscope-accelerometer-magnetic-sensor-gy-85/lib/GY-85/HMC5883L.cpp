#include "Arduino.h"
#include "I2CHelper.h"
#include "HMC5883L.h"
#include <math.h>

// Honeywell HMC5883L magnetometer
// https://www.adafruit.com/datasheets/HMC5883L_3-Axis_Digital_Compass_IC.pdf
// cfr. the datasheet at page 11
// 0x1E (11110) + 1 bit read write: 
// - 0x3C = read = B111100
// - 0x3D = write = B111101
#define HMC5883L_I2C 0x1E

#define MODE_REGISTER 0x02
#define CONTINUOUS_MEASUREMENT_MODE_VALUE 0x00

#define DATA_OUTPUT_X_REGISTER_A_MSB 0x03
// #define DATA_OUTPUT_X_REGISTER_B_LSB 0x04
// #define DATA_OUTPUT_Y_REGISTER_A_MSB 0x05
// #define DATA_OUTPUT_Y_REGISTER_B_LSB 0x06
// #define DATA_OUTPUT_Z_REGISTER_A_MSB 0x07
// #define DATA_OUTPUT_Z_REGISTER_B_LSB 0x08

// cfr. table at page 13
#define CONFIGURATION_REGISTER_B 0x01
// 0x20 = 32 according to the datasheet at page 13:
// CRB7 CRB6 CRB5 CRB4 CRB3 CRB2 CRB1 CRB0
//    0    0    1    0    0    0    0    0
#define GAIN_REGISTER_VALUE 0x20 // equivalent to digital resolution 0.92 mG/LSb
const float DIGITAL_RESOLUTION = 0.92; // cfr. table at page 13
const float GAUSS_FOR_GAIN_VALUE = 1090.0; // cfr. table at page 13
const float GAUS_TO_MICROTESLA = 100.0;

// The declination depends on the place on the earth were you are while running this code
// check it here: http://www.magnetic-declination.com
// My declination (in London, UK) for example is NEGATIVE (WEST): -0° 45' = -0.75°
const float DECLINATION_ANGLE = 0.75;

HMC5883L::HMC5883L():_i2CHelper(HMC5883L_I2C){}

void HMC5883L::init() {
  // set mode register to continuous measurement mode
  // this lets us make continuous reads of the axis data
  // otherwise by default the chip is in single read mode 
  // so then after reading from it once, it will go idle to save power
  _i2CHelper.writeToRegister(MODE_REGISTER, CONTINUOUS_MEASUREMENT_MODE_VALUE);
  // set the gain range
  _i2CHelper.writeToRegister(CONFIGURATION_REGISTER_B, GAIN_REGISTER_VALUE);
}

void HMC5883L::readMagnetometer(float *outXYZ) {
  byte magnetometerValues[6];
  // the output data is twos complement, 
  // with DATA_OUTPUT_X_REGISTER_A_MSB / DATA_OUTPUT_X_REGISTER_B_LSB 
  // for most/least significant bytes, repeated for X, Y, Z 
  // increasing by 1 the register address 
  _i2CHelper.readFromRegister(DATA_OUTPUT_X_REGISTER_A_MSB, 6, magnetometerValues);

  // X MSB | X LSB
  outXYZ[0] = ((((int)magnetometerValues[0]) << 8) | magnetometerValues[1]) / GAUSS_FOR_GAIN_VALUE * GAUS_TO_MICROTESLA; //* DIGITAL_RESOLUTION;
  // Y MSB | Y LSB
  outXYZ[1] = ((((int)magnetometerValues[2]) << 8) | magnetometerValues[3]) / GAUSS_FOR_GAIN_VALUE * GAUS_TO_MICROTESLA; // * DIGITAL_RESOLUTION;
  // Z MSB | Z LSB
  outXYZ[2] = ((((int)magnetometerValues[4]) << 8) | magnetometerValues[5]) / GAUSS_FOR_GAIN_VALUE * GAUS_TO_MICROTESLA; // * DIGITAL_RESOLUTION;
}

// The following conversion math is based on the Adafruit library
// cfr.: https://github.com/adafruit/Adafruit_HMC5883_Unified
float HMC5883L::convertToHorizontalYawHeading(float *outXYZ) {
  float horizontalYaw;

  // atan of Y/X
  horizontalYaw = atan2(outXYZ[1], outXYZ[0]);
  // declination adjustments
  horizontalYaw += DECLINATION_ANGLE;
  // Correct for when signs are reversed.
  if (horizontalYaw < 0) 
    horizontalYaw += 2*PI;
  // Check for wrap due to addition of declination.
  if (horizontalYaw > 2*PI) 
    horizontalYaw -= 2*PI;

  // Convert to degrees °
  horizontalYaw = horizontalYaw * 180/PI;

  // Serial.print("Converted heading: "); Serial.println(horizontalYaw);
  return horizontalYaw;
}



