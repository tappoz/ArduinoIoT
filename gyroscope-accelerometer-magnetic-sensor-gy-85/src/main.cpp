
// Cfr.:
// http://www.himix.lt/arduino/arduino-and-gy-85-9dof-accelerometer-adxl345-gyroscope-itg3200-and-magnetometer-hmc5883-angle-information-comparison/
// http://eeenthusiast.com/arduino-i2c-adxl-345-robot/
// https://github.com/sqrtmo/GY-85-arduino/blob/master/GY_85.cpp

#include <Wire.h>
#include <SPI.h>

// register cells
#define D0 1  // 2^0
#define D1 2  // 2^1
#define D2 4  // 2^2
#define D3 8  // 2^3
#define D4 16 // 2^4
#define D5 32 // 2^5
#define D6 64 // 2^6

// ADXL345 accelerometer address as specified in data sheet
// http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf
#define ADXL345 (0x53)

#define DATAX0 0x32 // X-Axis Data 0
// #define DATAX1 0x33 // X-Axis Data 1
// #define DATAY0 0x34 // Y-Axis Data 0
// #define DATAY1 0x35 // Y-Axis Data 1
// #define DATAZ0 0x36 // Z-Axis Data 0
// #define DATAZ1 0x37 // Z-Axis Data 1

#define POWER_CTL (0x2D)
#define DATA_FORMAT (0x31)

// milliseconds between reads
int DEVICE_SAMPLING_MS = 1500;

// writes value to address register on device
void writeToRegister(byte address, byte value) {
  Wire.beginTransmission(ADXL345);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

void initAccelerometer() {
  Wire.begin();
  // clear the POWER_CTL register
  writeToRegister(POWER_CTL, D0);
  // POWER_CTL D4 register high to make sure it is not in sleep mode
  writeToRegister(POWER_CTL, D4);
  // POWER_CTL D3 register high to set the module into measure mode
  writeToRegister(POWER_CTL, D3);

  // D1 D0 Range     byte
  //  0  0 +2/-2   g B00000000
  //  0  1 +4/-4   g B00000001
  //  1  0 +8/-8   g B00000010
  //  1  1 +16/-16 g B00000011
  // DATA_FORMAT D0 register to set the g range
  writeToRegister(DATA_FORMAT, B00000001);
}

void setup(){
  Serial.begin(9600);

  // initialise the accelerometer
  initAccelerometer();
}

void readAccelerometer(int *outXYZ) {

  Wire.beginTransmission(ADXL345);
  // the output data is twos complement, 
  // with DATAx0 as the least significant byte and DATAx1 as the most significant byte,
  // where x represent X, Y,  or Z
  Wire.write(DATAX0);
  Wire.endTransmission();

  Wire.beginTransmission(ADXL345);
  Wire.requestFrom(ADXL345, 6);

  int i = 0;
  byte accelerometer_values[6];
  while(Wire.available()){
    accelerometer_values[i] = Wire.read();
    // Serial.println("Current '" + String(i) + "': " + String(accelerometer_values[i]));
    i++;
  }
  Wire.endTransmission();

  outXYZ[0] = (((int)accelerometer_values[1]) << 8) | accelerometer_values[0]; 
  outXYZ[1] = (((int)accelerometer_values[3]) << 8) | accelerometer_values[2]; 
  outXYZ[2] = (((int)accelerometer_values[5]) << 8) | accelerometer_values[4];
}

void loop(){

  char accelerometer_output[512];
  int currentXYZ[3];
  readAccelerometer(currentXYZ);
  sprintf(accelerometer_output, "X=%d Y=%d Z=%d", currentXYZ[0], currentXYZ[1], currentXYZ[2]); 
  Serial.print(accelerometer_output); 
  Serial.write(10); 
  delay(DEVICE_SAMPLING_MS); 
}
