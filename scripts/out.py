import sys
import os

for f in os.listdir("./"):
  if ".mc" in f:
    os.system("python conv.py " + f)

print "done!"
  
