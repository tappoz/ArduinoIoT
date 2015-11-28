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

const String DATA_SEPARATOR = "#/#";
const char FIELD_SEPARATOR = '#';

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

  String xyzValues = String(currentXYZ[0], 4) + FIELD_SEPARATOR + String(currentXYZ[1], 4) + FIELD_SEPARATOR + String(currentXYZ[2], 4);

  return xyzValues;
}

String GY85::accelerometer() {
  float accXYZ[3];
  _accelerometer.readAccelerometer(accXYZ);

  String xyzValues = String();
  xyzValues = String(accXYZ[0], 4) + FIELD_SEPARATOR + String(accXYZ[1], 4) + FIELD_SEPARATOR + String(accXYZ[2], 4);
  
  return xyzValues;
}


String GY85::getFormattedDataRow() {
  String accelerometerValues = accelerometer();

  delay(10);
  String gyroscopeValues = gyroscope();

  delay(10);
  // in degree Celsius (°C)
  String temperatureValue = temperature();

  delay(10);
  // heading is the angle between the direction in which
  // the sensor nose is pointing
  // and the magnetich north as the reference direction
  // it is provided in degrees (°) in the range 0-360
  String headingValue = heading();

  String dataRow = String();
  dataRow = accelerometerValues + DATA_SEPARATOR + gyroscopeValues + DATA_SEPARATOR + temperatureValue + DATA_SEPARATOR + headingValue;

  return dataRow;
}
