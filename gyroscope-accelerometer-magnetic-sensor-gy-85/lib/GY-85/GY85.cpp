#include "Arduino.h"
#include "HMC5883L.h"
#include "GY85.h"

GY85::GY85() {}

void GY85::init() {
  _accelerometer.init();
  delay(10);
  _gyroscope.init();
  delay(10);
  _magnetometer.init();
  delay(10);
}

const String DEVICE_SEPARATOR = "*/*";
const String DATA_SEPARATOR = "*";

String GY85::heading() {
  float compassXYZ[3];
  _magnetometer.readMagnetometer(compassXYZ);
  float compassXYYaw = _magnetometer.convertToHorizontalYawHeading(compassXYZ);

  return String(compassXYYaw, 4);
}

String GY85::temperature() {
  float temperature;
  _gyroscope.readTemperature(&temperature);

  return String(temperature, 4);
}

String GY85::gyroscope() {
  float currentXYZ[3];
  _gyroscope.readGyroscope(currentXYZ);

  String xyzValues = String(currentXYZ[0], 4) + "*" + String(currentXYZ[1], 4) + "*" + String(currentXYZ[2], 4) + "*";

  return xyzValues;
}

String GY85::accelerometer() {
  int accXYZ[3];
  _accelerometer.readAccelerometer(accXYZ);

  String xyzValues = String();
  xyzValues = String(accXYZ[0]) + "*" + String(accXYZ[1]) + "*" + String(accXYZ[2]) + "*";
  
  return xyzValues;
}
