from subprocess import *
import os
import io
import re
import time

group_1_test_dir = "./test_file/group_1_test/test"
group_2_test_dir = "./test_file/group_2_test"
group_4_test_dir = "./test_file/group_4_test"
group_3_test_dir = "./test_file/group_3_test"
test_obj = "./development.exe"
max_log_file_line = 10000

test_cnt = 0
pass_cnt = 0

def input_test(file:io.TextIOWrapper, demo: Popen):
    iter_f = file.readlines()
    for line in iter_f:
        line = line.replace("\n", "").replace("\r", "")
        if len(line) > 0:
            line = line+'\n'
            demo.stdin.write(line.encode())
            demo.stdin.flush()
            # time.sleep(0.01)
    # demo.stdin.write("dump".encode())


def write_log(demo: Popen, dump_file: io.TextIOWrapper):
    demo.stdout.flush()
    out = demo.stdout.readlines(max_log_file_line)
    # out = out.decode().replace("/r", "")
    for line in out: 
        line = line.decode()
        line = line.replace("\n", "").replace("\r", "")
        line = line+'\n'
        dump_file.write(line)


def check_out(demo_out:io.TextIOWrapper, expect:io.TextIOWrapper, nameappend) -> bool:
    global pass_cnt
    test_lines = demo_out.readlines()
    expect_lines = expect.readlines()
    for i in range(len(expect_lines)):
        if "item3" in  expect_lines[i] or "stop" in expect_lines[i]:
            continue
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
            expect_line = expect_line.replace(" ", "")
            test_line = test_line.replace("\r", "")
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

def group_1_test(in_dir):
    global test_cnt
    files = os.listdir(in_dir)
    in_files = []
    out_files = []
    for file in files:
        if "input" in file:
            in_files.append(file)
        elif "dump" in file:
            out_files.append(file)
    sorted(in_files)
    sorted(out_files)
    file_num = len(in_files)
    for num in range(file_num):
        suffix = re.sub("[A-Za-z.]","",in_files[num])
        name_append = in_dir+suffix
        dump_file_name = in_dir+"/out"+suffix
        log_file_name = in_dir+"/log"+suffix
        dump_file = open(dump_file_name, "w+", encoding="utf-8")
        dump_file.truncate(0)
        in_file = open(in_dir+"/"+in_files[num], "r",encoding="utf-8")
        log = open(log_file_name, "w+", encoding="utf-8")
        log.truncate(0)
        demo = Popen([test_obj, dump_file_name], stdin=in_file, stdout=PIPE, stderr=STDOUT)
        test_cnt += 1
        # input_test(in_file, demo)
        time.sleep(0.1)
        write_log(demo, log)
        if demo.poll() == None:
            time.sleep(3)
            if demo.poll() == None:
                demo.kill()
                demo.wait()
                print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess timeout\n \033[0m")
                continue
            elif demo.poll() != 0:
                demo.wait()
                print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess exit incorrectly\n \033[0m")
            else:
                write_log(demo, log)
                demo.wait()
        elif demo.poll() == 0:
            write_log(demo, log)
            demo.wait()
        else:
            demo.wait()
            print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess exit incorrectly\n \033[0m") 
        out_file = open(in_dir+"/"+out_files[num], "r",encoding="utf-8")
        dump_file.seek(0,0)
        check_out(dump_file, out_file, name_append)
        dump_file.close()
        out_file.close()

def group_2_test(in_dir):
    dirs = os.listdir(in_dir)
    for dir in dirs:
        group_4_test(in_dir+"/"+dir)
            
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
        name_append = in_dir+"_{cnt}".format(cnt=num+1)
        dump_file_name = in_dir+"/dump"+"_{cnt}".format(cnt=num+1)
        log_file_name = in_dir+"/log"+"_{cnt}".format(cnt=num+1)
        dump_file = open(dump_file_name, "w+", encoding="utf-8")
        dump_file.truncate(0)
        in_file = open(in_dir+"/"+in_files[num], "r",encoding="utf-8")
        log = open(log_file_name, "w+", encoding="utf-8")
        log.truncate(0)
        demo = Popen([test_obj, dump_file_name], stdin=in_file, stdout=PIPE, stderr=STDOUT)
        test_cnt += 1
        # input_test(in_file, demo)
        time.sleep(0.1)
        write_log(demo, log)
        if demo.poll() == None:
            time.sleep(3)
            if demo.poll() == None:
                demo.kill()
                demo.wait()
                print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess timeout\n \033[0m")
                continue
            elif demo.poll() != 0:
                demo.wait()
                print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess exit incorrectly\n \033[0m")
            else:
                write_log(demo, log)
                demo.wait()
        elif demo.poll() == 0:
            write_log(demo, log)
            demo.wait()
        else:
            demo.wait()
            print("\033[1;34m"+"test  "+name_append+"\033[0m"+"\033[1;34m proess exit incorrectly\n \033[0m") 
        out_file = open(in_dir+"/"+out_files[num], "r",encoding="utf-8")
        dump_file.seek(0,0)
        check_out(dump_file, out_file, name_append)
        dump_file.close()
        out_file.close()

def group_3_test(in_dir):
    in_files = os.listdir(in_dir)
    for dir1_name in in_files:
        dir1_name = in_dir+"/"+dir1_name
        in_dir2s = os.listdir(dir1_name)
        for dir2_name in in_dir2s:
            dir2_name = dir1_name+"/"+dir2_name
            if os.path.isfile(dir2_name):
                group_process(dir1_name)
                break
            else:
                group_process(dir2_name)

def group_4_test(in_dir):
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
            write_log(demo, log)
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

print("test "+"group 1")
group_1_test(group_1_test_dir)
print("test "+"group 2")
group_2_test(group_2_test_dir)
print("test "+"group 3")
group_3_test(group_3_test_dir)
print("test "+"group 4")
group_4_test(group_4_test_dir)


print("summary:\033[1;35m pass {cnt} / {total} \033[0m!".format(cnt = pass_cnt, total = test_cnt))
