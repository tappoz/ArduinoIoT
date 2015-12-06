# Setup

Add the following lines to your `.bashrc` file so then you should be able to call the command `processing-java` 
from the command line.
```
# path to the processing-java binary
export PATH=$PATH:/YOUR/PATH/TO/processing-3.0.1
```

# Simulator

The serial port creation/mapping is done with `socat`:
```
$ socat -d -d pty,raw,echo=0,link=/tmp/ttyRX pty,raw,echo=0,link=/tmp/ttyTX
```
Where `/tmp/ttTX` is the port where the simulator writes data regarding the Arduino board and `/tmp/ttRX` is the port where the Processing dashboard is reading the data.

Run the simulator (written in python 2.7) from the command line like:
```
$ ./boardValuesSimulator.py
```

To check what is being written on the serial port use `screen` like:
```
$ screen /tmp/ttyRX 9600
```

When the Processing dashboard does not find any real board printing data on a USB serial port, then it assumes
there's a simulator running and printing data on `/tmp/ttyRX`.


# Build

Run the bash script `buil-processing.sh`. It should generate the java code and bytecode inside the folder `bytecode-out`
and run the java process for that bytecode.

