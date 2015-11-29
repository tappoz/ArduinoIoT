import processing.serial.*;

void setup() {
  size(1000, 500);
  setupBoardData();
}


void draw() {
  
  resetScreen();
  text("Listening to: " + usbPort, 50, 50);
  
  String currentDataRow = getDataRow();
  DataRow currentDataRowObj = processDataRow(currentDataRow);
  drawDataRow(currentDataRowObj);

  delay(1000);
}
