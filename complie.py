from subprocess import *
import os
import io
import re
import time

output_dir = "./build"
src_dir = "./development/"
if os.path.exists(output_dir) != True:
    os.mkdir(output_dir)
command = "gcc "+ src_dir+"*.c " +"-o development.exe"
print(command)
os.system(command)
