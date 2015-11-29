
void resetScreen() {  
  background(0); // Set background to black
  fill(46, 209, 2);
}

void drawDataRow(DataRow inputDataRaw) {
  drawAccelerometerData(inputDataRaw);
  drawGyroscopeData(inputDataRaw);
  text("Temperature: " + inputDataRaw.temperature + " °C", 50, 140);
  text("Heading: " + inputDataRaw.heading + " °", 50, 150);
}

private void drawAccelerometerData(DataRow inputDataRaw) {
  text("Accelerometer", 50, 60);
  text("X: " + inputDataRaw.accelerometerX + " G", 50, 70);
  text("Y: " + inputDataRaw.accelerometerY + " G", 50, 80);
  text("Z: " + inputDataRaw.accelerometerZ + " G", 50, 90);
}

private void drawGyroscopeData(DataRow inputDataRaw) {
  text("Gyroscope:", 50, 100);
  text("X: " + inputDataRaw.gyroscopeX + " °/s", 50, 110);
  text("Y: " + inputDataRaw.gyroscopeY + " °/s", 50, 120);
  text("Z: " + inputDataRaw.gyroscopeZ + " °/s", 50, 130);
}
