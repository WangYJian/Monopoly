<<<<<<< HEAD
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
=======
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
>>>>>>> 5f4f82de58a62597f02d8980b98f6584ed8dc227
