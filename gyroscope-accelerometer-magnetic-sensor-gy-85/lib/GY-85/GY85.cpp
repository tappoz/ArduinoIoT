#include "Arduino.h"
#include "HMC5883L.h"
#include "GY85.h"

GY85::GY85() {
  // _magnetometer = new HMC5883L();
}

// void GY85::init() {
//   _magnetometer = new HMC5883L();
// }

void GY85::heading(String &headingStr) {
  float compassXYZ[3];
  _magnetometer.readMagnetometer(compassXYZ);
  float compassXYYaw = _magnetometer.convertToHorizontalYawHeading(compassXYZ);

  headingStr = String(compassXYYaw, 4);
}
