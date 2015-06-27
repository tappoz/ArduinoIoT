# Slider & LED

This small project shows how to switch on/off a LED by evaluating the signal of a slider used as a commander.

## Hardware

You need:
- _Arduino Uno R3_;
- _LED_ on the pins `GND` and `13`;
- _slider_ on the pins `A0` (the signal) and the couple `5V` and `GND` for the power supply.

The slider I've been using is a `Bourns Inc. PTA6043-2015DPB103 POTENTIOMETER, SLIDE, 10K, 20%, 0.25W`. From the datasheet you could find out:
- Pin 2: the slide gang;
- Pin 1, 3: GND and 5V.

![The setup](/doc/ArduinoUno_Slider_LED.jpg)

## Software

The source code is written in javascript for the _Node.js_ platform. The main library is [Johnny-Five](http://johnny-five.io).

To get started you need:
* The Arduino IDE running the _Firmata_ package (File -> Example -> Firmata -> StandardFirmata);
* Check that the Arduino board is properly _connected via USB_ to your computer (under linux run `lsusb | grep Arduino` on the command line to check the board is connected and running);
* Select the Arduino UNO board from the IDE (Tools -> Board -> Arduino UNO);
* Select the COM port from the IDE (Tools -> Serial Port -> /dev/ttyACM0);
* Upload the Firmata source code to the board via the Arduino IDE clicking on the Upload button.

At this point the Node.js code running on your laptop (basically the Johnny-Five _npm_ module) will use the Firmata code running on the board as an API.

From the command line you should be able to run the source code using the `node` command:
```
$ node slider-with-led.js 
1435411275762 Device(s) /dev/ttyACM0 
1435411275780 Connected /dev/ttyACM0 
1435411279120 Repl Initialized 
>> off: 0.39100684261974583
on: 0.5865102639296188
on: 0.6842619745845552
on: 0.5865102639296188
on: 0.6842619745845552
on: 0.8797653958944281
on: 0.6842619745845552
on: 0.6842619745845552
off: 0.2932551319648094

(^C again to quit)
>> 
1435411290860 Board Closing. 
$
```
