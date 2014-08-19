import socket

serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("connectiing")

serversocket.connect(("192.168.1.142",6000))
print("connected")
while True:
	serversocket.send(b'sending')
	data = serversocket.recv(1024)
	print (data)
