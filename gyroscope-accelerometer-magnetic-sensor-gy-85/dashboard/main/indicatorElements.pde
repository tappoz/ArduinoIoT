
// TODO work on this:
// https://github.com/jarzebski/Arduino-HMC5883L/blob/master/Processing/HMC5883L_processing/HMC5883L_processing.pde
// TODO make the heading adjustments as in the previous repository
void drawCompass(int x, int y, float heading, PImage plate) {
  int compassWidth = plate.width;
  pgCompassPlate = createGraphics(compassWidth, compassWidth); 

  float north = 180 + heading;
  
  pgCompassPlate.beginDraw();
  pgCompassPlate.clear();
  pgCompassPlate.translate(100,100);
  pgCompassPlate.rotate(-radians(heading));
  pgCompassPlate.image(plate, -100, -100);
  pgCompassPlate.endDraw();

  image(pgCompassPlate, x+30, y+30);

  textAlign(CENTER);
  text((int)heading+" deg", x+130, y+265);
  textAlign(LEFT);
}
