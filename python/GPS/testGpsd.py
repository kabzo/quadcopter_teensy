#befor you run this program you have to connect gps with : sudo gpsd /dev/ttyAMA0
import os
from gps import *
from time import *
import time
import threading
 
gpsd = None #seting the global variable
 
os.system('clear') #clear the terminal (optional)
os.system('sudo gpsd /dec/ttyAMA0')

class GpsPoller(threading.Thread):
  def __init__(self):
    threading.Thread.__init__(self)
    global gpsd #bring it in scope
    gpsd = gps(mode=WATCH_ENABLE) #starting the stream of info
    self.current_value = None
    self.running = True #setting the thread running to true
 
  def run(self):
    global gpsd
    while gpsp.running:
      gpsd.next() #this will continue to loop and grab EACH set of gpsd info to clear the buffer
 
if __name__ == '__main__':
  gpsp = GpsPoller() # create the thread
  try:
    gpsp.start() # start it up
    while True:
      #It may take a second or two to get good data
      #print gpsd.fix.latitude,', ',gpsd.fix.longitude,'  Time: ',gpsd.utc
 	os.system('clear')
	lat = gpsd.fix.latitude
	lot = gpsd.fix.longitude 
      	print
      	print ' GPS reading'
      	print '----------------------------------------'
	#if lat != 0  and lot != 0:
      	print 'latitude    ' , gpsd.fix.latitude
      	print 'longitude   ' , gpsd.fix.longitude
   	print 'time utc    ' , gpsd.utc,' + ', gpsd.fix.time
	print 'altitude (m)' , gpsd.fix.altitude
 	print 'speed (m/s) ' , gpsd.fix.speed
	
      	time.sleep(5) #set to whatever
 
  except (KeyboardInterrupt, SystemExit): #when you press ctrl+c
    print "\nKilling Thread..."
    gpsp.running = False
    gpsp.join() # wait for the thread to finish what it's doing
  print "Done.\nExiting."
