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
  
  if(previousDataRow != null) {
    println("Sending x_prev " + previousDataRow.millis + " x_curr " + currentDataRowObj.millis + " y_prev " + previousDataRow.temperature + " y_curr " + currentDataRowObj.temperature);
    drawTemperature((float) previousDataRow.millis, (float) currentDataRowObj.millis, (float) previousDataRow.temperature, (float) currentDataRowObj.temperature);
  } else {
    println("Something may be wrong!");
  }

  previousDataRow = currentDataRowObj;

  delay(1000);
}
