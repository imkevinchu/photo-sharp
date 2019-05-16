#!/usr/bin/python

import os
import sys


file = sys.argv[1]

line1 = "./microc.native " + file + " > " + file + ".ll"
line2 = "/usr/local/opt/llvm/bin/llc -relocation-model=pic " + file + ".ll > " + file + ".s"
line3 = "cc -o " + file + ".exe " + file + ".s printbig.o psharplib.o pixel.o Album.o ImageStack.o"
line4 = "./" + file + ".exe"

os.system(line1)
os.system(line2)
os.system(line3)
os.system(line4)

os.system("rm -f " + file + ".s " + file + ".ll " + file + ".exe")
