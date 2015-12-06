#!/usr/bin/env python2.7

import sched, time
import gy85_utils.sensors_simulator as helpers_sensor_data
import gy85_utils.serial_simulator as helpers_serial

chosen_port_tx = '/tmp/ttyTX'
helpers_serial.init(chosen_port_tx)

data_separator = "#/#"

def concatenate_chunks(input_scheduler, previous_temp, previous_heading):
  current_gyroscope_triple     = helpers_sensor_data.generate_random_gyroscope_triple()
  current_accelerometer_triple = helpers_sensor_data.generate_random_accelerometer_triple()
  current_temp                 = helpers_sensor_data.generate_random_temp(previous_temp)
  current_heading              = helpers_sensor_data.generate_random_heading(previous_heading)

  current_data_row = data_separator.join((current_accelerometer_triple, current_gyroscope_triple, "%.4f" % current_temp, "%.4f" % current_heading))
  helpers_serial.print_to_serial(current_data_row + '\n')

  input_scheduler.enter(delay, priority, concatenate_chunks, (input_scheduler, current_temp, current_heading,))


delay = 1 # seconds
priority = 1

initial_temperature = 15.0
initial_heading = 180.0

board_simulator = sched.scheduler(time.time, time.sleep)

board_simulator.enter(delay, priority, concatenate_chunks, (board_simulator, initial_temperature, initial_heading,))
board_simulator.run()

