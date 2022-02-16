
import socket
from botvalue_pb2 import botdata
import sys

addr_confm = ('ip', 12345)

clic = socket.socket(socket.AF_INET, s$
clic.bind(addr_confm)
clic.listen(5)
cl, addr = clic.accept()
print "Get Data(Y/N)? :" , sys.argv[0]
enter = sys.argv[0]
cl.send(enter)

cl.close()




