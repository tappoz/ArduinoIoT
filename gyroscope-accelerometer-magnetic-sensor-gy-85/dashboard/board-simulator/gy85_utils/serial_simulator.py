import subprocess, serial
import pty
import os

# http://stackoverflow.com/questions/5411780/python-run-a-daemon-sub-process-read-stdout
def init_virtual_serial_channel(port_tx):
  # socat -d -d pty,raw,echo=0,link=/tmp/ttyRX pty,raw,echo=0,link=/tmp/ttyTX
  socat_cmd = "socat -d -d pty,raw,echo=0,link=/tmp/ttyRX pty,raw,echo=0,link=" + port_tx
  socat_master, socat_slave = pty.openpty()
  # running socat in background
  socat_proc = subprocess.Popen(socat_cmd, shell=True, stdin=subprocess.PIPE, stdout=socat_slave, stderr=socat_slave, close_fds=True)
  socat_stdout = os.fdopen(socat_master)
  # "starting data transfer"
  check_socat_output = True
  while check_socat_output:
    socat_line = socat_stdout.readline()
    if "starting data transfer loop with FDs [3,3] and [5,5]" in socat_line:
      print "The socat command has been initialised, returning!"
      check_socat_output = False
      return

usb_serial_com = None

def init(port_tx):
  init_virtual_serial_channel(port_tx)
  global usb_serial_com
  usb_serial_com = serial.Serial(port_tx,9600,timeout=5)
  # dont open the serial port! it is opened by `socat`!

def print_to_serial(data_row):
  usb_serial_com.write(data_row)
