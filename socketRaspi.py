import socket
import time
import sys
from socketClass import *
import threading
import serial 

#sock = mysocket()
ser = serial.Serial('/dev/ttyUSB0',115200)


PORTSEND = 6000
PORTRECEIVE = 4444

def socket_send(portConnect):
	#sock = mysocket()
	print "connecting send"
	sock.connect("192.168.1.142",portConnect)
	print "sacesfull connected sending "
	while True:
		try:
			sock.mysend(ser.readline())
		except socket.error, e:
			print "Connection broken"
			break
#		time.sleep(1000)
#		sock.myreceive()

sockReceive = mysocket()

def socket_receive(portSend):
	print "connecting to receive"
	sockReceive.connect("192.168.1.142",portSend)
	print "sacesfull connected, receieving"
	while True:
		print sock.myreceive()

if __name__ == '__main__':
# 	threadSend = threading.Thread(target = socket_send, args = (PORTSEND, ))
#	threadSend.start()
#	socket_send(PORTSEND)
#	print"done"
	threadReceive = threading.Thread(target = socket_receive,args = (PORTRECEIVE,))
	threadReceive.start()
#	print "go"
	#socket_send(PORT)
