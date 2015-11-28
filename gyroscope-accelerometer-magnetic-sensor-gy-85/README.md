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
```

## Useful commands

To get information about the memory usage of the compiled file etc.:
```
.pioenvs/uno$ avr-size firmware.elf
.pioenvs/uno$ readelf -a firmware.elf
.pioenvs/uno$ avr-objdump -d firmware.elf
```
