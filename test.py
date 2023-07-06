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



def input_all_test_file(in_dir, out_dir, name_append)->bool:
    print("\n")
    print("test "+name_append)
    in_files = os.listdir(in_dir)
    out_files = os.listdir(out_dir)
    global test_cnt
    for file_name in in_files:
        if os.path.isdir(in_dir+"/"+file_name):
            if os.path.exists(dump_dir+"/"+file_name) != True:
                os.mkdir(dump_dir+"/"+file_name)
            if os.path.exists(log_dir+"/"+file_name) != True:
                os.mkdir(log_dir+"/"+file_name)
            input_all_test_file(in_dir+"/"+file_name, out_dir+"/"+file_name, name_append+file_name)
        elif os.path.isfile(in_dir+"/"+file_name):
            suffix = re.sub("[A-Za-z.]", "", file_name)
            dump_file_name = dump_dir+"/"+name_append+"/out"+suffix
            log_file_name = log_dir+"/"+name_append+"/log"+suffix
            dump_file = open(dump_file_name, "w+", encoding="utf-8")
            dump_file.truncate(0)
            in_file = open(in_dir+"/"+file_name, "r",encoding="utf-8")
            log = open(log_file_name, "w+", encoding="utf-8")
            log.truncate(0)
            demo = Popen([test_obj, dump_file_name], stdin=PIPE, stdout=log, stderr=STDOUT)
            test_cnt += 1
            input_test(in_file, demo)
            time.sleep(0.1)
            if demo.poll() == None:
                time.sleep(3)
                if demo.poll() == None:
                    print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess timeout\n \033[0m")
                    continue
            elif demo.poll() != 0:
                print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess exit incorrectly\n \033[0m")
            # write_dump(demo, dump_file)
            out_file_name = [v for v in out_files if suffix in v]
            out_file = open(out_dir+"/"+out_file_name[0], "r", encoding="utf-8")
            dump_file.seek(0,0)
            check_out(dump_file, out_file, name_append)
            dump_file.close()
            # demo.kill()
            # demo.wait()
            out_file.close()
            

if os.path.exists(dump_dir) != True:
    os.mkdir(dump_dir)
if os.path.exists(log_dir) != True:
    os.mkdir(log_dir)

input_all_test_file(test_input_dir, test_output_dir, "")

print("summary:\033[1;35m pass {cnt} / {total} \033[0m!".format(cnt = pass_cnt, total = test_cnt))
