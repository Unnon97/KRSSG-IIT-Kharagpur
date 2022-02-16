import socket 
from botvalue_pb2 import botdata
import sys

addr_confm = ('ip', 12345)

sc = socket.socket(socket.AF_INET,socket.SOCK_STREAM,0)		#sock for confirmation
sc.connect(addr_confm)
cfm = sc.recv(16)
sc.close()
	