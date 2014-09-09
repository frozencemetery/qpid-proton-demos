#!/usr/bin/python

import sys

from proton import *

def main(argv):
  if len(argv) < 3:
    print "Usage: %s <addr> <message...>" % argv[0]
    return 1
  addr = argv[1]
  data = ' '.join(argv[2:])

  sendmsg = Message()
  sendmsg.address = addr
  sendmsg.subject = data

  m = Messenger()
  m.start() # required but currently a no-op
  m.subscribe(addr)

  m.put(sendmsg)
  m.send() # block

  recvmsg = Message()
  m.recv() # block
  m.get(recvmsg)

  print "Got: \"%s\"" % recvmsg.subject

  m.accept()

  return 0

if __name__ == "__main__":
  exit(main(sys.argv))
