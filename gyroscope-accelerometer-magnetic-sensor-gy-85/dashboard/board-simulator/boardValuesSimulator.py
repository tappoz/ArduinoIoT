#!/usr/bin/env python2.7

import sched, time, serial
import gy85_utils.sensor_signal as helpers

data_separator = "#/#"

delay = 1 # seconds
priority = 1

initial_temperature = 15.0
initial_heading = 180.0

board_simulator = sched.scheduler(time.time, time.sleep)


port = '/tmp/ttyTX'
usb_serial_com = serial.Serial(port,9600,timeout=5)
# dont open the serial port! it is opened by `socat`! usb_serial_com.open()

def print_to_serial(data_row):
  # usb_serial_com.flush()
  usb_serial_com.write(data_row)


def concatenate_chunks(input_scheduler, previous_temp, previous_heading):
    current_gyroscope_triple = helpers.generate_random_gyroscope_triple()
    current_accelerometer_triple = helpers.generate_random_accelerometer_triple()
    current_temp = helpers.generate_random_temp(previous_temp)
    current_heading = helpers.generate_random_heading(previous_heading)

    current_data_row = data_separator.join((current_accelerometer_triple, current_gyroscope_triple, "%.4f" % current_temp, "%.4f" % current_heading))
    print current_data_row
    print_to_serial(current_data_row + '\n')

    input_scheduler.enter(delay, priority, concatenate_chunks, (input_scheduler, current_temp, current_heading,))

board_simulator.enter(delay, priority, concatenate_chunks, (board_simulator, initial_temperature, initial_heading,))
board_simulator.run()

