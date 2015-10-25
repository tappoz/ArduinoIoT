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

I think that with the g set to +4/-4 (`DATA_FORMAT` register) the maximum should be 125 with errors around +/- 25

| Position            | X  | Y  | Z  |
|---------------------|----|----|----|
|Flat                 |  0 |  0 |  1 |
|Antiflat             |  0 |  0 | -1 |
|Side pins on flat    |  1 |  0 |  0 |
|Side pins on antiflat| -1 |  0 |  0 |
|VCC on flat          |  0 | -1 |  0 |
|VCC on antiflat      |  0 |  1 |  0 |

