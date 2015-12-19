IoT projects with Arduino
=========================

| Description | Path |
|-------------|------|
| This project involves Jhonny-Five (the javascript framework for IoT) and Node.js to switch on a LED using a threshold value coming from a slider | [node-js-slider-led](./node-js-slider-led) |
| This project uses a couple of Arduino UNO boards with a Nordic nrf24l01+ transceiver each to send each other a radio message, the C++ code is managed by platformIO (a tool chain for Arduino boards) | [nrf24l01-radio](./nrf24l01-radio) |
| This projects shows information about the sensors in the GY-85, a 9DOF IMU (9 degrees of freedom inertial measurement unit) providing an accelerometer, a gyroscope, a magnetic sensor and a temperature sensor. The library to manage the GY-85 has been written by me, using I2C communications. There's also a dashboard (written in Processing) to visualise the sensor measurements (e.g. a compass). To run the dashboard a board simulator has also been provided. The simulator is written in python 2.7 and spits data on a virtual serial port in the same way a real board would do. | [gyroscope-accelerometer-magnetic-sensor-gy-85](./gyroscope-accelerometer-magnetic-sensor-gy-85) |
