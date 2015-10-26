#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
#include "I2CHelper.h"

I2CHelper::I2CHelper(uint8_t i2cAddress) {
  _deviceI2CAddress = i2cAddress;
}

// writes value to address register on device at i2cAddress
void I2CHelper::writeToRegister(byte address, byte value) {
  Wire.beginTransmission(_deviceI2CAddress);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

// It reads numOfBytes (the expected length of the input/output array)
// starting from registerAddress on device at i2cAddress into the input/output _buffForDataBytes[]
void I2CHelper::readFromRegister(byte registerAddress, int numOfBytes, byte _buffForDataBytes[]) {
  Wire.beginTransmission(_deviceI2CAddress);
  Wire.write(registerAddress);
  Wire.endTransmission();
  
  Wire.beginTransmission(_deviceI2CAddress);
  Wire.requestFrom(_deviceI2CAddress, numOfBytes);
  
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
