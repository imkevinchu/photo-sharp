import sys
import os

def main():
 
  f = open(sys.argv[1], "r")
  o = open("temp.txt", "w")

  for line in f:
    for word in line.split(" "):
      print word
      if ("prints" in word):
        line = line.replace("prints", "print")
      if ("printb" in word and "printbig" not in word):
        line = line.replace("printb", "print")
      if ("printf" in word):
        line = line.replace("printf", "print")

    o.write(line)

#  semi = False
#  for line in f:
#    for character in line:
#      if character == ';':
#        semi = True
#        continue
#      if semi == True:
#        semi = False
#        if character == '\n':
#          o.write("\n")
#        else:
#          o.write(";")
#          o.write(character)
#      else:
#        o.write(character)

  f.close()
  o.close()
 
  f = open(sys.argv[1], "w")
  o = open("temp.txt", "r")

  for line in o:
    f.write(line)

  f.close()
  o.close()

  os.system("rm temp.txt")

main()
