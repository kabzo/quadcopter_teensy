import serial
import os
cmd = "raspivid -o - -t 0 -hf -w 800 -h 400 -fps 24 |cvlc -vvv stream:///dev/stdin --sout '#standard{access=http,mux=ts,dst=:8160}' :demux=h264"
print cmd

#subrocess.call(cmd,shell = True) #eneble camera
os.system('clear')
ser = serial.Serial('/dev/ttyUSB0',115200)

while 1:
	print ser.readline()
