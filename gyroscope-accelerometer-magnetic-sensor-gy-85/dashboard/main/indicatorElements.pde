
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

// offset to remove the initial value of the milliseconds 
// when printing the x axis values of the temperature graph
float x_offset;

// https://people.cs.pitt.edu/~jwenskovitch/processing.html
// http://www.openprocessing.org/sketch/223971
void initTemperatureGraph(float input_x_offset) {
  // 46, 209, 2 -> 2E, D1, 02
  // color lineForeground = #2ED102;
  // stroke(lineForeground);
  stroke(46, 209, 2);
  strokeWeight(4);
  x_offset = input_x_offset;
}

// TODO check this http://www.gicentre.net/utils/chart/
// TODO check also this https://www.arduino.cc/en/Tutorial/Graph
// TODO check also https://itp.nyu.edu/physcomp/labs/labs-serial-communication/serial-output-from-an-arduino/
// TODO check also http://www.engineersgarage.com/contribution/temperature-plot-using-processing-and-arduino

// TODO keep track of the previous N pairs, then loop on them with the current values

void drawTemperature(float x_previous, float x_current, float y_previous, float y_current) {
  // map(value, actual_start1, actual_stop1, target_start2, target_stop2)
  float x_prev = map((x_previous - x_offset), 0, 60000, 0, 60);
  float x_curr = map((x_current - x_offset), 0, 60000, 0, 60);

  float window_x_prev = 50 + x_prev;
  float window_x_curr = 50 + x_curr;
  // float window_y_prev = 300 + map(y_previous, -10, 30, 0, 100);
  // float window_y_curr = 300 + map(y_current, -10, 30, 0, 100);
  float window_y_prev = 300 + map(y_previous, 0, 20, 0, 100);
  float window_y_curr = 300 + map(y_current, 0, 20, 0, 100);

  println("x_prev " + window_x_prev + " y_prev " + window_y_prev + " x_curr " + window_x_curr + " y_curr " + window_y_curr);

  line(window_x_prev, window_y_prev, window_x_curr, window_y_curr);
}

