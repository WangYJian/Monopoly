from subprocess import *
import os
import io
import re
import time

test_dir = "E:/c++/richman/Monopoly/test_file"
test_input_dir = test_dir+"/input"
test_output_dir = test_dir+"/output"
dump_dir = test_dir+"/dump"
test_obj = "E:/c++/richman/Monopoly/build/development.exe"
log_dir = test_dir+"/log"

test_cnt = 0
pass_cnt = 0

def input_test(file:io.TextIOWrapper, demo: Popen):
    iter_f = file.readlines()
    cnt = 0
    for line in iter_f:
        if len(line) > 0:
            demo.stdin.write(line.encode())
            demo.stdin.flush()
    # demo.stdin.write("dump".encode())


def write_dump(demo: Popen, dump_file: io.TextIOWrapper):
    out, err = demo.communicate()
    out = out.decode().replace("\r", "")
    dump_file.write(out)


def check_out(demo_out:io.TextIOWrapper, expect:io.TextIOWrapper, nameappend) -> bool:
    global pass_cnt
    test_lines = demo_out.readlines()
    expect_lines = expect.readlines()
    for i in range(len(expect_lines)):
        expect_line = expect_lines[i].replace(" ", "").replace("\n", "").replace("\r", "")
        if i >= len(test_lines):
            str1 = "\033[1;34m"+"test  "+nameappend+"\033[0m \033[1;31m error \033[0m"
            str2 = "error in \033[1;36m line {line_num} \033[0m".format(line_num=i)
            str3 = "expect: "+ "\033[1;35m"+ expect_line.replace("\n", "").replace("\r", "") +"\033[0m"
            str4 = "\033[1;33m get to the end of dump file \033[0m"
            print(str1+":  "+str2+"    "+str3+"     "+str4)
            return False
        else:
            test_line = test_lines[i].replace(" ", "").replace("\n", "") 
            test_line = ''.join(sorted(test_line))
            expect_line = ''.join(sorted(expect_line))
            expect_line = expect_line.replace(" ", "").replace("\n", "").replace("\r", "")
            test_line = test_line.replace(" ", "").replace("\n", "").replace("\r", "")
            expect_lines[i] = expect_lines[i].replace("\n", "").replace("\r", "")
            test_lines[i] = test_lines[i].replace("\n", "").replace("\r", "")
            if test_line != expect_line:
                str1 = "\033[1;34m"+"test  "+nameappend+"\033[0m \033[1;31m error \033[0m"
                str2 = "error in \033[1;36m line {line_num} \033[0m".format(line_num=i)
                str3 = "expect: "+ "\033[1;35m"+ expect_lines[i] +"\033[0m".replace("\n", "").replace("\r", "")
                str4 = "get: "+"\033[1;33m"+ test_lines[i] +"\033[0m".replace("\n", "").replace("\r", "")
                print(str1+":  "+str2+"    "+str3+"     "+str4)
                return False
    print("\033[1;34m"+"test"+nameappend+"\033[0m \033[1;32m pass \033[0m")
    pass_cnt += 1
    return True