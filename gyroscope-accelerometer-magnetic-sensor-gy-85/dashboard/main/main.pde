import processing.serial.*;

PGraphics pgCompassPlate;
PImage imgCompassPlateWhite;

void setup() {
  size(1000, 500);
  setupBoardData();
  imgCompassPlateWhite = loadImage("compassPlateWhite.png");
  println("Image width: " + imgCompassPlateWhite.width);
}

void draw() {
  
  resetScreen();
  text("Listening to: " + usbPort, 50, 50);
  
  String currentDataRow = getDataRow();
  DataRow currentDataRowObj = processDataRow(currentDataRow);
  drawDataRow(currentDataRowObj);

  drawCompass(480, 5, (float)currentDataRowObj.heading, imgCompassPlateWhite);

  delay(1000);
}
