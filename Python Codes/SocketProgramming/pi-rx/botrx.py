import socket
from botvalue_pb2 import botdata
import sys

addr_data = ('ip' , 12340)


clid = socket.socket(socket.AF_INET, s$
clid.connect(addr_data)
data = botdata()
data.ParseFromString(clid.recv(1024))
print "botid = " , data.botid
print "Vel1 = " , data.v1
print "Vel2 = " , data.v2
print "Vel3 = " , data.v3
print "Vel4 = " , data.v4
print "Battery stat = " , data.batstat
print "Kicker voltage = " , data.capvol
clid.close()
