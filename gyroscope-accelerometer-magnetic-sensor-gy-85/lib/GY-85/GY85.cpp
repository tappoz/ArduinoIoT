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

const String DEVICE_SEPARATOR = "*/*";
const String DATA_SEPARATOR = "*";

// String formatData()
// String GY85::getData(String *data, int len) {
//   String result = "";
//   for (int i = 0; i < len; i++) {
//     result += data[i] + DEVICE_SEPARATOR;
//     Serial.println(result);
//   }
//   return result.substring(0, result.length() - 1);
// }

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

