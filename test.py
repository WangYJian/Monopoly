from subprocess import *
import os
import io
import re
import time

group_2_test_dir = "./test_file/group_2_test"
test_input_dir = group_2_test_dir+"/input"
test_output_dir = group_2_test_dir+"/output"
group_4_test_dir = "./test_file/group_4_test"
group_3_test_dir = "./test_file/group_3_test"
dump_dir = group_2_test_dir+"/dump"
test_obj = "./development.exe"
log_dir = group_2_test_dir+"/log"
max_log_file_line = 1000

test_cnt = 0
pass_cnt = 0

def input_test(file:io.TextIOWrapper, demo: Popen):
    iter_f = file.readlines()
    for line in iter_f:
        if len(line) > 0:
            demo.stdin.write(line.encode())
            demo.stdin.flush()
    # demo.stdin.write("dump".encode())


def write_log(demo: Popen, dump_file: io.TextIOWrapper):
    out = demo.stdout.readlines(max_log_file_line)
    for line in out:
    # out = out.decode().replace("/r", "")
        dump_file.write(line.decode())


def check_out(demo_out:io.TextIOWrapper, expect:io.TextIOWrapper, nameappend) -> bool:
    global pass_cnt
    test_lines = demo_out.readlines()
    expect_lines = expect.readlines()
    for i in range(len(expect_lines)):
        expect_line = expect_lines[i].replace("\n", "").replace("\r", "")
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
    print("\033[1;34m"+"test  "+nameappend+"\033[0m \033[1;32m pass \033[0m")
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
            demo = Popen([test_obj, dump_file_name], stdin=in_file, stdout=PIPE, stderr=STDOUT)
            test_cnt += 1
            # input_test(in_file, demo)
            time.sleep(0.1)
            if demo.poll() == None:
                time.sleep(1)
                if demo.poll() == None:
                    write_log(demo, log)
                    demo.kill()
                    demo.wait()
                    print("\033[1;34m"+"test  "+name_append+suffix+"\033[0m"+"\033[1;34m proess timeout\n \033[0m")
                    continue
                elif demo.poll() != 0:
                    # demo.wait()
                    print("\033[1;34m"+"test  "+name_append+suffix+"\033[0m"+"\033[1;34m proess exit incorrectly\n \033[0m")
            elif demo.poll() == 0:
                write_log(demo, log)
                # demo.wait()
            out_file_name = [v for v in out_files if suffix in v]
            out_file = open(out_dir+"/"+out_file_name[0], "r", encoding="utf-8")
            dump_file.seek(0,0)
            check_out(dump_file, out_file, name_append+suffix)
            dump_file.close()
            out_file.close()
            
def group_process(in_dir):
    global test_cnt
    in_suffix = ".in"
    out_suffix = ".out"
    files = os.listdir(in_dir)
    in_files = []
    out_files = []
    for file in files:
        if in_suffix in file:
            in_files.append(file)
        elif out_suffix in file:
            out_files.append(file)
    sorted(in_files)
    sorted(out_files)
    file_num = len(in_files)
    for num in range(file_num):
        name_append = in_dir+"_{cnt}".format(cnt=num)
        dump_file_name = in_dir+"/dump"+"_{cnt}".format(cnt=num)
        log_file_name = in_dir+"/log"+"_{cnt}".format(cnt=num)
        dump_file = open(dump_file_name, "w+", encoding="utf-8")
        dump_file.truncate(0)
        in_file = open(in_dir+"/"+in_files[num], "r",encoding="utf-8")
        log = open(log_file_name, "w+", encoding="utf-8")
        log.truncate(0)
        demo = Popen([test_obj, dump_file_name], stdin=in_file, stdout=PIPE, stderr=STDOUT)
        test_cnt += 1
    # input_test(in_file, demo)
        time.sleep(0.1)
        if demo.poll() == None:
            time.sleep(1)
            if demo.poll() == None:
                write_log(demo, log)
                demo.kill()
                demo.wait()
                print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess timeout\n \033[0m")
                continue
            elif demo.poll() != 0:
                # demo.wait()
                print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess exit incorrectly\n \033[0m")
        elif demo.poll() == 0:
            write_log(demo, log)
            # demo.wait()
        out_file = open(in_dir+"/"+out_files[num], "r",encoding="utf-8")
        dump_file.seek(0,0)
        check_out(dump_file, out_file, name_append)
        dump_file.close()
        out_file.close()

def group_3_test(in_dir):
    print("\n")
    print("test "+"group 4")
    in_files = os.listdir(in_dir)
    global test_cnt
    for dir1_name in in_files:
        dir1_name = in_dir+"/"+dir1_name
        in_dir2s = os.listdir(dir1_name)
        for dir2_name in in_dir2s:
            dir2_name = dir1_name+"/"+dir2_name
            if os.path.isfile(dir2_name):
                group_process(dir1_name)
            else:
                group_process(dir2_name)

def group_4_test(in_dir):
    print("\n")
    print("test "+"group 3")
    in_files = os.listdir(in_dir)
    global test_cnt
    for dir_name in in_files:
        dir_name = in_dir+"/"+dir_name
        name_append = dir_name
        if os.path.isdir(dir_name):
            dump_file_name = dir_name+"/dump"
            log_file_name = dir_name+"/log"
            dump_file = open(dump_file_name, "w+", encoding="utf-8")
            dump_file.truncate(0)
            in_file = open(dir_name+"/input", "r",encoding="utf-8")
            log = open(log_file_name, "w+", encoding="utf-8")
            log.truncate(0)
            demo = Popen([test_obj, dump_file_name], stdin=in_file, stdout=PIPE, stderr=STDOUT)
            test_cnt += 1
            # input_test(in_file, demo)
            time.sleep(0.1)
            if demo.poll() == None:
                time.sleep(1)
                if demo.poll() == None:
                    write_log(demo, log)
                    demo.kill()
                    demo.wait()
                    print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess timeout\n \033[0m")
                    continue
                elif demo.poll() != 0:
                    # demo.wait()
                    print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess exit incorrectly\n \033[0m")
            elif demo.poll() == 0:
                write_log(demo, log)
                # demo.wait()
            out_file_name = dir_name+"/output"
            out_file = open(out_file_name, "r", encoding="utf-8")
            dump_file.seek(0,0)
            check_out(dump_file, out_file, name_append)
            dump_file.close()
            out_file.close()    

if os.path.exists(dump_dir) != True:
    os.mkdir(dump_dir)
if os.path.exists(log_dir) != True:
    os.mkdir(log_dir)

group_3_test(group_3_test_dir)
group_4_test(group_4_test_dir)
input_all_test_file(test_input_dir, test_output_dir, "")

print("summary:\033[1;35m pass {cnt} / {total} \033[0m!".format(cnt = pass_cnt, total = test_cnt))
