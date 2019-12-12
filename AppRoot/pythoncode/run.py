import subprocess
import sys
import os

command_str= "python " + os.getcwd()+'\\pythoncode\\'
for i in range(1,len(sys.argv)):
    command_str = command_str + sys.argv[i] + ' '
#print(command_str)
p1 = subprocess.Popen(["cmd", "/C", command_str],stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
print(p1.communicate()[0].decode('ANSI'),end='')
