import processing.serial.*;

PGraphics pgCompassPlate;
PImage imgCompassPlateWhite;

void setup() {
  size(1000, 500);
  setupBoardData();
  imgCompassPlateWhite = loadImage("compassPlateWhite.png");
  // println("Image width: " + imgCompassPlateWhite.width);
  initTemperatureGraph(millis());
}

DataRow previousDataRow = null;

void draw() {
  
  resetScreen();
  text("Listening to: " + usbPort, 50, 50);
  
  String currentDataRowStr = getDataRow();
  DataRow currentDataRowObj = processDataRow(currentDataRowStr);
  
  drawDataRow(currentDataRowObj);
  drawCompass(480, 5, (float)currentDataRowObj.heading, imgCompassPlateWhite);
  drawTemperature((float) currentDataRowObj.millis, (float) currentDataRowObj.temperature);

  delay(1000);
}
