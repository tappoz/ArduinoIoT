
PFont monospaced;

void resetScreen() {
  // set the font
  monospaced = createFont("Monospaced", 9);
  textFont(monospaced);
  // set background to black
  background(0);
  // set font color to green
  fill(46, 209, 2);
}

void drawDataRow(DataRow inputDataRaw) {
  drawAccelerometerData(inputDataRaw);
  drawGyroscopeData(inputDataRaw);
  text("Temperature: " + nfs((float)inputDataRaw.temperature, 2, 4) + " °C", 50, 140);
  text("Heading: " + nfs((float)inputDataRaw.heading, 3, 2) + " °", 50, 150);
}

private void drawAccelerometerData(DataRow inputDataRaw) {
  text("Accelerometer", 50, 60);
  text("X: " + nfs((float)inputDataRaw.accelerometerX, 2, 4) + " G", 50, 70);
  text("Y: " + nfs((float)inputDataRaw.accelerometerY, 2, 4) + " G", 50, 80);
  text("Z: " + nfs((float)inputDataRaw.accelerometerZ, 2, 4) + " G", 50, 90);
}

private void drawGyroscopeData(DataRow inputDataRaw) {
  text("Gyroscope:", 50, 100);
  text("X: " + nfs((float)inputDataRaw.gyroscopeX, 2, 4) + " °/s", 50, 110);
  text("Y: " + nfs((float)inputDataRaw.gyroscopeY, 2, 4) + " °/s", 50, 120);
  text("Z: " + nfs((float)inputDataRaw.gyroscopeZ, 2, 4) + " °/s", 50, 130);
}
