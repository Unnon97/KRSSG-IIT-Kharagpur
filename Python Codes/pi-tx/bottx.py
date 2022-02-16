import socket 
from botvalue_pb2 import botdata
import sys

data = botdata()
def values(data):
	data.botid = 1
	data.v1 = 10
	data.v2 = 30
	data.v3 = 50
	data.v4 = 70
	data.batstat = 19
	data.capvol = 50
	return;

addr_data = ('ip',12340)			#address for data

while True:
	sd = socket.socket(socket.AF_INET,socket.SOCK_STREAM,0)		#sock for data
	sd.bind(addr_data)
	sd.listen(5)
	print "Sending"
	c, addr = sd.accept()
	values(data)
	buf = data.SerializeToString()
	c.send(buf)
	print "sent"
c.close()	


