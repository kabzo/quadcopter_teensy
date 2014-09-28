import socket
import time
import sys
import threading
#import serial

#ser = serial.Serial('/dev/ttyUSB0',115200)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IPADRESS = "192.168.1.4"
PORT = 6000

def socket_connect(sockConnect):
	check = False
	while not check:
		try:
			print "Connecting"
			sockConnect.connect((IPADRESS,PORT))
			check = True
		except socket.error as e:
			print "Connection error:" + "Could not connect to IP {ipAdress} and port {port}".format(ipAdress = IPADRESS,port = PORT)
			time.sleep(1)
	
	if check:
		print "Sacesfully connected to IP {ipAdress} and port {port}".format(ipAdress = IPADRESS,port = PORT)
		print ""
		return 1

					
def socket_send():
	while True:
		# time.sleep(0.04);
		try:
			sock.send("1234567890")
		except socket.error as e:
			print "Connection broken while sending"
			break

def socket_receive():
    while True:
        try:
        	data = sock.recv(1024)
        	if not data:
        		print "Socket connection broken"
        	else:
        		if data[0] == 'C':
        			print "Controll SEQUENZ:" + data
        		else:
        			print data
        except socket.error as e:
        	print "Connection broken while receiving"
        	break

if __name__ == '__main__':
	if socket_connect(sock) == 0 :
		quit()
	threadSend = threading.Thread(target = socket_send)
	threadSend.start()
	print "threadSend STARTED"
	threadReceive = threading.Thread(target = socket_receive)
	threadReceive.start()
	print "threadReceive STARTED"
    


