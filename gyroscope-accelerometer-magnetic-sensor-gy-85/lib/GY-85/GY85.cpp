#include "Arduino.h"
#include "HMC5883L.h"
#include "GY85.h"

GY85::GY85() {}

void GY85::init() {
  _magnetometer.init();
}

String GY85::heading() {
  float compassXYZ[3];
  _magnetometer.readMagnetometer(compassXYZ);
  float compassXYYaw = _magnetometer.convertToHorizontalYawHeading(compassXYZ);

  return String(compassXYYaw, 4);
}
