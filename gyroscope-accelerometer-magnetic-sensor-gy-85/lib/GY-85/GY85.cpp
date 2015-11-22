#include "Arduino.h"
#include "HMC5883L.h"
#include "GY85.h"

GY85::GY85() {}

void GY85::init() {
  _magnetometer.init();
  delay(10);
  _gyroscope.init();
  // delay(10);
}

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
