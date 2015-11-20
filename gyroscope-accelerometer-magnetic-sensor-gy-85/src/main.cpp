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
#include <MemoryFree.h>

// milliseconds between reads
const int DEVICE_SAMPLING_MS = 2000;

ADXL345 accelerometer;
ITG3200 gyroscope;
HMC5883L magnetometer;

GY85 inertialMeasurementUnit;

void setup(){
  Serial.begin(9600);

  // initialise the accelerometer
  // accelerometer.init();
  // byte currentRange;
  // accelerometer.getGRange(&currentRange);

  // TODO: fix the following one...
  // Serial.println("Current range: " + currentRange);

  // gyroscope.init();

  inertialMeasurementUnit.init();
}

void loop(){

  // new line
  Serial.write('\n');

  char accOutput[512];

  // int currentXYZ[3];
  // accelerometer.readAccelerometer(currentXYZ);
  // sprintf(accOutput, "Accelerometer X=%d Y=%d Z=%d", currentXYZ[0], currentXYZ[1], currentXYZ[2]); 
  // Serial.println(accOutput);

  // delay(10);

  // gyroscope.readGyroscope(currentXYZ);
  // sprintf(accOutput, "Gyroscope °/s X=%d Y=%d Z=%d", currentXYZ[0], currentXYZ[1], currentXYZ[2]); 
  // Serial.println(accOutput);

  // delay(10);

  // float temperature;
  // gyroscope.readTemperature(&temperature);
  // Serial.print("Temerature ");
  // printDouble(temperature, 2);
  // Serial.println("°C");

  delay(10);

  String heading = inertialMeasurementUnit.heading();
  Serial.println("Heading: " + heading);

  delay(DEVICE_SAMPLING_MS);
}
