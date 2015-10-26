#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include "I2CHelper.h"

I2CHelper::I2CHelper() {
  // do nothing in the constructor
}

// writes value to address register on device at i2cAddress
void I2CHelper::writeToRegister(uint8_t i2cAddress, byte address, byte value) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

// It reads numOfBytes (the expected length of the input/output array)
// starting from registerAddress on device at i2cAddress into the input/output _buffForDataBytes[]
void I2CHelper::readFromRegister(uint8_t i2cAddress, byte registerAddress, int numOfBytes, byte _buffForDataBytes[]) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(registerAddress);
  Wire.endTransmission();
  
  Wire.beginTransmission(i2cAddress);
  Wire.requestFrom(i2cAddress, numOfBytes);
  
  int i = 0;
  while (Wire.available()) { 
    _buffForDataBytes[i] = Wire.read();
    // Serial.println("Current '" + String(i) + "': " + String(_buffForDataBytes[i]));
    i++;
  }
  if (i != numOfBytes) {
    // TODO SOMETHING HERE!
    Serial.println("More data than expected: " + String(i));
  }
  Wire.endTransmission();
}
