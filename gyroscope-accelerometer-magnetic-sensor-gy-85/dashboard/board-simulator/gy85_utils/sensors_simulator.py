import random

temperature_min = -10.0
temperature_max = 30.0

def get_temp_boundaries(current_temp):
  temp_step = random.uniform(0.0, 2.0)
  upper_bound = current_temp + temp_step
  if upper_bound > temperature_max:
    upper_bound = temperature_max
  lower_bound = current_temp - temp_step
  if lower_bound < temperature_min:
    lower_bound = temperature_min

  return (lower_bound, upper_bound)

def generate_random_temp(current_temp):
  lower_bound, upper_bound = get_temp_boundaries(current_temp)
  random_number = random.uniform(lower_bound,upper_bound)

  return random_number

# ----------------------------------------------------

degree_min=0.0
degree_max=360.0

def get_degrees_boundaries(current_degree):
  degree_step = random.uniform(0.0, 5.0)
  upper_bound = current_degree + degree_step
  if upper_bound > degree_max:
    upper_bound = degree_max
  lower_bound = current_degree - degree_step
  if lower_bound < degree_min:
    lower_bound = degree_min

  return (lower_bound, upper_bound)

def generate_random_heading(current_degree):
  lower_bound, upper_bound = get_degrees_boundaries(current_degree)
  random_degree = random.uniform(lower_bound, upper_bound)

  return random_degree

# ----------------------------------------------------

field_separator = "#"

def generate_random_gyroscope_triple():
  gyro_x = random.uniform(-10, 10)
  gyro_y = random.uniform(-10, 10)
  gyro_z = random.uniform(-10, 10)

  return "%.4f" % gyro_x + field_separator + "%.4f" % gyro_y + field_separator + "%.4f" % gyro_z

def generate_random_accelerometer_triple():
  accelerometer_x = random.uniform(-2, 2)
  accelerometer_y = random.uniform(-2, 2)
  accelerometer_z = random.uniform(-2, 2)

  return "%.4f" % accelerometer_x + field_separator + "%.4f" % accelerometer_y + field_separator + "%.4f" % accelerometer_z

