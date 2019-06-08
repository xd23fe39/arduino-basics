#!/usr/bin/python
import serial
import syslog
import time

#The following line is for serial over GPIO
port = '/dev/ttyUSB0'


ard = serial.Serial(port,9600,timeout=5)

i = 0

while (Serial.available()):
    # Serial read section
    msg = ard.read(ard.inWaiting()) # read everything in the input buffer
    print ("Message from arduino: ")
    print (msg)
    i = i + 1
else:
    print "Exiting"
exit()