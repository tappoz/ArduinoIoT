import processing.serial.*;

void setup() {
  size(1000, 500);
  setupBoardData();
}


void draw() {
  
  resetScreen();
  text("Test on: " + usbPort, 50, 50);
  
  text(getDataRow(), 100, 100);
  
}