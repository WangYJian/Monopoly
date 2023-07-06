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
log = open("./log", "w+", encoding='utf-8')

def input_test(file, demo: Popen):
    iter_f = iter(file)
    for line in iter_f:
        demo.stdin.write(line.encode())
    demo.stdin.write("dump".encode())


def write_dump(demo: Popen, dump_file: io.TextIOWrapper):
    out, err = demo.communicate()
    out = out.decode().replace("\r", "")
    dump_file.write(out)


def check_out(demo_out:io.TextIOWrapper, expect:io.TextIOWrapper, suffix) -> bool:
    test_lines = demo_out.readlines()
    expect_lines = expect.readlines()
    for i in range(len(expect_lines)):
        expect_line = expect_lines[i].replace(" ", "").replace("\n", "")
        if i >= len(test_lines):
            print("\033[1;34m"+"test"+suffix+"\033[0m \033[1;31m error \033[0m")
            print("error in \033[1;36m line {line_num} \033[0m".format(line_num=i))
            print("expect: "+ "\033[1;35m"+ expect_line +"\033[0m")
            print("\033[1;33m get to the end of dump file \033[0m")
            return False
        else:
            test_line = test_lines[i].replace(" ", "").replace("\n", "") 
            if test_line != expect_line:
                print("\033[1;34m"+"test"+suffix+"\033[0m \033[1;31m error \033[0m")
                print("error in \033[1;36m line {line_num} \033[0m".format(line_num=i))
                print("expect: "+ "\033[1;35m"+ expect_line +"\033[0m")
                print("get: "+"\033[1;33m"+ test_line +"\033[0m")
                return False
    print("\033[1;34m"+"test"+suffix+"\033[0m \033[1;32m pass \033[0m")
    return True



def input_all_test_file(in_dir, out_dir, name_append)->bool:
    print("\n\n\n")
    print("test "+name_append)
    in_files = os.listdir(in_dir)
    out_files = os.listdir(out_dir)
    for file_name in in_files:
        if os.path.isdir(in_dir+"/"+file_name):
            if os.path.exists(dump_dir+"/"+file_name) != True:
                os.mkdir(dump_dir+"/"+file_name)
            input_all_test_file(in_dir+"/"+file_name, out_dir+"/"+file_name, file_name)
        elif os.path.isfile(in_dir+"/"+file_name):
            suffix = re.sub("[A-Za-z.]", "", file_name)
            dump_file_name = dump_dir+"/"+name_append+"/out"+suffix
            dump_file = open(dump_file_name, "w+", encoding="utf-8")
            dump_file.truncate(0)
            demo = Popen([test_obj, dump_file_name], stdin=PIPE, stdout=PIPE, stderr=STDOUT)
            in_file = open(in_dir+"/"+file_name, "r",encoding="utf-8")
            input_test(in_file, demo)
            time.sleep(0.5)
            # write_dump(demo, dump_file)
            out_file_name = [v for v in out_files if suffix in v]
            out_file = open(out_dir+"/"+out_file_name[0], "r", encoding="utf-8")
            dump_file.seek(0,0)
            check_out(dump_file, out_file, suffix)
            dump_file.close()
            demo.kill()
            demo.wait()
            out_file.close()
            

if os.path.exists(dump_dir) != True:
    os.mkdir(dump_dir)

input_all_test_file(test_input_dir, test_output_dir, "")

print("This is a \033[1;35m test \033[0m!")
