

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

// TODO http://pastebin.com/kSrU3nVH
// TODO https://www.youtube.com/watch?v=IpIf_qB5-K8

float[] lastTemperatures = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float[] lastTimestamps = {65.0, 65.0, 65.0, 65.0, 65.0, 65.0, 65.0, 65.0, 65.0, 65.0};

float sumArray(float[] array, int index) {
  float sum = 0.0;
  for (int i = 0; i <= index; i++) {
    sum += array[i];
  }
  return sum;
}

float[] shiftLeftArray(float[] array) {
  float firstElement = array[0];
  for (int i = 1 ; i < (array.length-1) ; i++) {
    array[i] = array[i+1];
  }
  array[array.length - 1] = firstElement;
  return array;
}

void drawTemperature(float x_current, float y_current) {

  // map(value, actual_start1, actual_stop1, target_start2, target_stop2)
  float x_curr = map((x_current - x_offset), 0, 60000, 0, 60);
  float window_x_curr = 50 + x_curr;
  float window_y_curr = 300 + map(y_current, 0, 20, 0, 100);

  lastTemperatures = shiftLeftArray(lastTemperatures);
  lastTimestamps = shiftLeftArray(lastTimestamps);

  // update the last N elements of valid data
  lastTemperatures[lastTemperatures.length - 1] = window_y_curr;
  lastTimestamps[lastTimestamps.length - 1] = window_x_curr;
  
  for(int i=1; i<lastTemperatures.length; i++) {
    point(sumArray(lastTimestamps, i), lastTemperatures[i]);
  }
}

