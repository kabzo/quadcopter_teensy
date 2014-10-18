import socket
import time
import sys
import threading
import serial

global ser
try:
#	global ser
	ser = serial.Serial('/dev/ttyACM1',115200)
	print "serial Connected"
except:
	print "serial ERROR"
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IPADRESS = "192.168.1.4"
PORT = 6000

connection = False

def socket_connect(sockConnect):
	check = False
	while not check:
		try:
			print "Connecting"
			sockConnect.connect((IPADRESS,PORT))
			check = True
			connection = True
		except socket.error as e:
			print "Connection error:" + "Could not connect to IP {ipAdress} and port {port}".format(ipAdress = IPADRESS,port = PORT)
			connection = False
			time.sleep(1)
	
	if check:
		print "Sacesfully connected to IP {ipAdress} and port {port}".format(ipAdress = IPADRESS,port = PORT)
		print ""
	

					
def socket_send():
	while True:
		try:
			if ser:
				data = ser.readline()
				sock.send(data)
		except socket.error as e:
			connection = False
			print "Connection broken while sending"
			break

def socket_receive():
    while True:
        try:
        	data = sock.recv(1024)
        	if not data:
        		print "Socket connection broken"
			break
        	else:
			if ser:
				ser.write(data)
      				print data
        except socket.error as e:
        	connection = False
        	print "Connection broken while receiving"
        	break

if __name__ == '__main__':
		socket_connect(sock)	
		threadSend = threading.Thread(target = socket_send)
		threadSend.start()
		print "threadSend STARTED"
		threadReceive = threading.Thread(target = socket_receive)
		threadReceive.start()
		print "threadReceive STARTED"
		
    


