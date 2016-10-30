import serial
import time

ser = serial.Serial('/dev/cu.usbmodem1421', 9600, timeout=0)

target = open('data', 'w')

while 1:
    try:
    	if(ser.readline() != ''):
	    	target.write(ser.readline() + '\n')
#        print(ser.readline())
        time.sleep(1/10)
    except ser.SerialTimeoutException:
    	target.write('Data could not be read')
        time.sleep(1/10)