#include "Arduino.h"
#include <SPI.h>
#include "I2CHelper.h"
#include "ITG3200.h"

// ITG3200 gyroscope
// http://www.invensense.com/products/motion-tracking/3-axis/itg-3200/
// http://43zrtwysvxb2gf29r5o0athu.wpengine.netdna-cdn.com/wp-content/uploads/2015/02/ITG-3200-Datasheet.pdf
// http://43zrtwysvxb2gf29r5o0athu.wpengine.netdna-cdn.com/wp-content/uploads/2015/02/ITG-3200-Register-Map.pdf
// AD0 1101000 I2C address
#define ITG3200_I2C (0x68)

// ITG3200 (register map, page 6)
// Power Management
#define PWR_MGM (0x3E)
// Sample Rate Divider
#define SMPLRT_DIV (0x15)
// Digital Low Pass Filter/ Full Scale range
#define DLPF_FS (0x16)
// Interrupt: Configuration
#define INT_CFG (0x17)

// temperature sensor
#define TEMP_OUT_H (0x1B)
#define GYRO_XOUT_H (0x1D)
#define GYRO_YOUT_H (0x1F)
#define GYRO_ZOUT_H (0x21)

ITG3200::ITG3200():_i2CHelper(ITG3200_I2C){}

void ITG3200::init() {

  // reset the power management register
  _i2CHelper.writeToRegister(PWR_MGM, 0x00);
  // set the full scale register
  // 0x1E: 
  // * FS_SEL (Bit4,Bit3) = 3 = +/- 2000 dgrs/sec
  // * DLPF_CFG (Bit2,Bit1,Bit0) = 6 = Digital Low Pass Filter Bandwidth 5Hz / Internal Sample Rate 1KHz
  _i2CHelper.writeToRegister(DLPF_FS, 0x1E);
  // set the sampling rate divider register
  // 7 means 8ms per sample
  _i2CHelper.writeToRegister(SMPLRT_DIV, 0x07);
  // reset the interrupt configuration register
  _i2CHelper.writeToRegister(INT_CFG, 0x00);

  delay(10);
  
  // GyroCalibrate();
}

void ITG3200::readGyroscope(int *outGyroXYZ) {
  byte gyroscopeValues[6];
  
  _i2CHelper.readFromRegister(GYRO_XOUT_H, 6, gyroscopeValues);

  outGyroXYZ[0] = (((int)gyroscopeValues[0]) << 8) | gyroscopeValues[1]; 
  outGyroXYZ[1] = (((int)gyroscopeValues[2]) << 8) | gyroscopeValues[3]; 
  outGyroXYZ[2] = (((int)gyroscopeValues[4]) << 8) | gyroscopeValues[5];
}

void ITG3200::readTemperature(float *tempCelsius) {
  byte _tempBuff[2];

  _i2CHelper.readFromRegister(TEMP_OUT_H,2,_tempBuff);
  // Celsius (cfr. the table in the datasheet at page 7)
  // * temperature offset: -13200 (means 35°C)
  // * sensitivity: 280 (every 1°C)
  // * range: -30°C/+85°C
  // So the temperature in °C is: T = 35° + (value + 13200)/280;
  // the Fahrenheit conversion is: F=C*9/5+32
  *tempCelsius = 35 + ((_tempBuff[0] << 8 | _tempBuff[1]) + 13200) / 280.0;
}

