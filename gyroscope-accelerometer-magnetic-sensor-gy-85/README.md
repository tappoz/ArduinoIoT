Inertial measurement unit (IMU) GY-85
=====================================

## Pin setup

| GY-85  | Arduino UNO |
|--------|-------------|
| VCC_IN | 5V          |
| GND    | GND         |
| SCL    | A5          |
| SDA    | A4          |


## Software lifecycle

```
$ platformio serialports list
/dev/ttyUSB0
------------
Hardware ID: USB VID:PID=1a86:7523
Description: QinHeng Electronics HL-340 USB-Serial adapter

$ platformio run --target upload --upload-port /dev/ttyUSB0

$ platformio serialports monitor --port /dev/ttyUSB0
```

## Expected output data

Run the following command with the board connected to the USB port:
```
$ platformio run --target upload --upload-port /dev/ttyUSB0
```
Then you should see the "CSV" like records show up in the terminal:
```
$ platformio serialports monitor --port /dev/ttyUSB0
[...]
-0.1094#-0.0938#0.9453#/#4.8000#-0.2783#-0.0696#/#19.8071#/#302.9341
-0.1094#-0.0859#0.9531#/#4.8000#-0.2783#0.0000#/#19.8000#/#302.9760
-0.1094#-0.0859#0.9531#/#4.7304#-0.3478#0.0000#/#19.8214#/#302.7963
-0.1094#-0.0859#0.9453#/#4.7304#-0.2783#-0.0696#/#19.7821#/#302.9760
-0.1172#-0.0938#0.9453#/#4.8000#1.8783#5.0087#/#19.8143#/#302.7413
0.0781#-0.7578#0.5313#/#-10.5739#-11.5478#11.2000#/#19.7857#/#276.4858
0.0313#-0.5000#0.8047#/#26.5043#9.5304#-20.5217#/#19.7643#/#293.6818
-0.1406#-0.8516#0.3750#/#-8.0696#-7.3739#45.9826#/#19.6750#/#287.7943
```

Where every row contains X,Y,Z from the accelerometer (in `G`), then X,Y,Z from the gyroscope (in `°/s`), then the temperature (in `°C`), then the heading (in `°`). The separator for X,Y,Z is `#`. The separator for different sensor measurements is `#/#`.

## Useful commands

The folder where platformIO compiles, links e prepare all the steps to generate the firmware is `.pioenvs`. That gets generated when the `platformio` command is run on the command line.

To get information about the memory usage of the compiled file etc.:
```
.pioenvs/uno$ avr-size firmware.elf
.pioenvs/uno$ readelf -a firmware.elf
.pioenvs/uno$ avr-objdump -d firmware.elf
```

To see the decompiled content of a `.o` file:
```
$ avr-objdump -S .pioenvs/uno/GY-85/ITG3200.o
```
