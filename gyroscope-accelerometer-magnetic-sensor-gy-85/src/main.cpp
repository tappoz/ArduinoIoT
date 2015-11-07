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
#include <MemoryFree.h>

// milliseconds between reads
const int DEVICE_SAMPLING_MS = 600;

ADXL345 accelerometer;
ITG3200 gyroscope;
HMC5883L magnetometer;


// source: http://forum.arduino.cc/index.php/topic,44216.0.html#13
void printDouble( double val, byte precision){
  // prints val with number of decimal places determine by precision
  // precision is a number from 0 to 6 indicating the desired decimial places
  // example: printDouble( 3.1415, 2); // prints 3.14 (two decimal places)

  if(val < 0.0){
    Serial.print('-');
    val = -val;
  }

  Serial.print (int(val)); // prints the int part
  if (precision > 0) {
    Serial.print("."); // prints the decimal point
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
      mult *= 10;

    if (val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;
    while (frac1 /= 10 )
      padding--;
      while (padding--)
        Serial.print("0");
        Serial.print(frac,DEC);
  }
}



void setup(){
  Serial.begin(9600);

  // initialise the accelerometer
  accelerometer.init();
  byte currentRange;
  accelerometer.getGRange(&currentRange);

  // TODO: fix the following one...
  Serial.println("Current range: " + currentRange);

  gyroscope.init();
  magnetometer.init();
}

void loop(){

  char accOutput[512];
  int currentXYZ[3];
  accelerometer.readAccelerometer(currentXYZ);
  sprintf(accOutput, "Accelerometer X=%d Y=%d Z=%d", currentXYZ[0], currentXYZ[1], currentXYZ[2]); 
  Serial.print(accOutput); 
  Serial.write(10); 

  gyroscope.readGyroscope(currentXYZ);
  sprintf(accOutput, "Gyroscope X=%d Y=%d Z=%d", currentXYZ[0], currentXYZ[1], currentXYZ[2]); 
  Serial.print(accOutput); 
  Serial.write(10); 

  char temperatureOutput[50];
  float temperature;
  gyroscope.readTemperature(&temperature);
  Serial.print("Temerature ");
  printDouble(temperature, 2);
  Serial.println("°C");

  magnetometer.readMagnetometer(currentXYZ);
  sprintf(accOutput, "Magnetometer X=%d Y=%d Z=%d", currentXYZ[0], currentXYZ[1], currentXYZ[2]); 
  Serial.print(accOutput); 
  Serial.write(10);

  Serial.print("Free memory: ");
  Serial.println(freeMemory());

  // delete[] accOutput;
  // delete[] currentXYZ;

  delay(DEVICE_SAMPLING_MS);
}
