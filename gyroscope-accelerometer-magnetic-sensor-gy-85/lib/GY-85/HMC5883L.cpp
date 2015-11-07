#include "Arduino.h"
#include "I2CHelper.h"
#include "HMC5883L.h"
#include <math.h>

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

// cfr. table at page 13
#define CONFIGURATION_REGISTER_B 0x01
#define GAIN_REGISTER_VALUE 0x01 // equivalent to digital resolution 0.92 mG/LSb
const float DIGITAL_RESOLUTION = 0.92;

// The declination depend on the place on the earth were you are while running this code
// check it here: http://www.magnetic-declination.com
// My declination (in London, UK) for example is NEGATIVE (WEST): -0° 45' = -0.75°
const float DECLINATION_ANGLE = 0.75;

HMC5883L::HMC5883L():_i2CHelper(HMC5883L_I2C){}

void HMC5883L::init() {
  // set mode register to continuous measurement mode
  _i2CHelper.writeToRegister(MODE_REGISTER, 0x00);
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

  outXYZ[0] = ((((int)magnetometerValues[0]) << 8) | magnetometerValues[1]) * DIGITAL_RESOLUTION;
  outXYZ[1] = ((((int)magnetometerValues[2]) << 8) | magnetometerValues[3]) * DIGITAL_RESOLUTION;
  outXYZ[2] = ((((int)magnetometerValues[4]) << 8) | magnetometerValues[5]) * DIGITAL_RESOLUTION;
}

float HMC5883L::convertToHorizontalYawHeading(float *outXYZ) {
  float horizontalYaw;

  // atan of Y/X
  horizontalYaw = atan2(outXYZ[1], outXYZ[0]);
  // declination adjustments
  horizontalYaw += DECLINATION_ANGLE;
  // Correct for when signs are reversed.
  if (horizontalYaw < 0) horizontalYaw += 2*PI;
  // Check for wrap due to addition of declination.
  if (horizontalYaw > 2*PI) horizontalYaw -= 2*PI;

  // Convert to degrees °
  horizontalYaw = horizontalYaw * 180/PI;

  return horizontalYaw;
}



