import java.lang.Exception;
import java.lang.Double;


static final String DATA_SEPARATOR = "#/#";
static final String FIELD_SEPARATOR = "#";

DataRow processDataRow(String dataRowStr) {
  DataRow dataRow = new DataRow();
  try {
    mapDataRow(dataRowStr, dataRow);
  } catch (Exception e) {
    println("ERROR: " + e.getMessage());
  }
  return dataRow;
}

private static void mapDataRow(String dataRowStr, DataRow dataRow) {
  // process the entire row
  String[] dataChunks = dataRowStr.split(DATA_SEPARATOR);
  // process the chunks
  String[] accelerometerXYZ = dataChunks[0].split(FIELD_SEPARATOR);
  String[] gyroscopeXYZ = dataChunks[1].split(FIELD_SEPARATOR);
  String temperature = dataChunks[2];
  String heading = dataChunks[3];
  // build the object fields
  dataRow.accelerometerX = Double.parseDouble(accelerometerXYZ[0]);
  dataRow.accelerometerY = Double.parseDouble(accelerometerXYZ[1]);
  dataRow.accelerometerZ = Double.parseDouble(accelerometerXYZ[2]);
  dataRow.gyroscopeX = Double.parseDouble(gyroscopeXYZ[0]);
  dataRow.gyroscopeY = Double.parseDouble(gyroscopeXYZ[1]);
  dataRow.gyroscopeZ = Double.parseDouble(gyroscopeXYZ[2]);
  dataRow.temperature = Double.parseDouble(temperature);
  dataRow.heading = Double.parseDouble(heading);
}
