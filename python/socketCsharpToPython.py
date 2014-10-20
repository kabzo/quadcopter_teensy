import socket
import time
import sys
import threading
import serial

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IPADRESS = "192.168.1.4"
PORT = 6000
connection = False
def serial_connect(adress,ser):
	try:
		# global ser
		ser = serial.Serial(adress,115200)
		print "serial Connected"
		return True
	except:
		print "serial ERROR"
		return False

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
	

					
def socket_send(ser):
	while True:
		try:
			if ser:
				data = ser.readline()
				sock.send(data)
		except socket.error as e:
			connection = False
			print "Connection broken while sending"
			break

def socket_receive(ser):
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
	ser = None
	arduinoArdress = '/dev/ttyACM'
	for count in range(0,20):
		connection_ser = serial_connect(arduinoArdress+str(count),ser)
		if connection_ser:
			print "Connecting to:"+arduinoArdress+str(count)
			break
	socket_connect(sock)	
	threadSend = threading.Thread(target = socket_send,arg=(ser,))
	threadReceive = threading.Thread(target = socket_receive,arg=(ser,))
	threadSend.start()
	print "threadSend STARTED" 
	threadReceive.start()
	print "threadReceive STARTED"

	while True:
		if not threadSend.isAlive():
			print "connection with ground station broken"
	
		
    


