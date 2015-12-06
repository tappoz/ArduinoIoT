String usbPort = "";
private Serial boardWithIMU;

String simulatorSerialPort = "/tmp/ttyRX";
String getUSBPort() {
   for(String port : Serial.list()) {
     if (port.contains("USB")) {
       println("Found it! " + port);
       return port;
     }
   }
   println(":( no USB here... Returning the simulator port: " + simulatorSerialPort);
   return simulatorSerialPort;
}

void setupBoardData() {
  usbPort = getUSBPort();
  boardWithIMU = new Serial(this, usbPort, 9600);
  boardWithIMU.bufferUntil('\n');
}

String previousReading = "";
String getDataRow() {
  String currentReading = "";
  if (boardWithIMU.available() > 0) {
    currentReading = boardWithIMU.readStringUntil('\n');
    if (null != currentReading) {
      previousReading = currentReading;
      println("Found this current: " + currentReading);
    } else {
      println("Data is null");
    }
  }
  return previousReading;
}
