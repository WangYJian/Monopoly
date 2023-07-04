from subprocess import *
import os
import io
import re
import time

test_input_dir = "./test_file/input"
test_output_dir = "./test_file/output"
dump_dir = "./test_file/dump"


def input_test(file, demo: Popen):
    iter_f = iter(file)
    for line in iter_f:
        demo.stdin.write(line.encode())
    demo.stdin.write("dump".encode())


def write_dump(demo: Popen, dump_file: io.TextIOWrapper):
    out, err = demo.communicate()
    out = out.decode().replace("\r", "")
    dump_file.write(out)


def check_out(demo_out, expect) -> bool:
    test_out = demo_out.read()
    expect_out = expect.read()
    test_out = test_out.replace(" ", "").replace("\n", "")
    expect_out = expect_out.replace(" ", "").replace("\n", "")
    return test_out == expect_out


def input_all_test_file(in_dir, out_dir):
    in_files = os.listdir(in_dir)
    for file_name in in_files:
        suffix = re.sub("[A-Za-z]", "", file_name)
        dump_file_name = dump_dir + "/out" + suffix
        dump_file = open(dump_file_name, "w+")
        dump_file.truncate(0)
        demo = Popen(
            [
                "./development/development.exe",
                in_dir + "/" + file_name,
                dump_file_name,
            ],
            stdin=PIPE,
            stdout=PIPE,
            stderr=STDOUT,
        )
        time.sleep(0.1)
        # in_file = open(in_dir+"/"+file_name, "r")
        # input_test(in_file, demo)
        # write_dump(demo, dump_file)
        out_file_name = "output" + suffix
        out_file = open(out_dir + "/" + out_file_name, "r")
        dump_file.seek(0, 0)
        if check_out(dump_file, out_file) == True:
            print("\033[1;34m" + "test" + suffix + "\033[0m \033[1;32m pass \033[0m")
        else:
            print("\033[1;34m" + "test" + suffix + "\033[0m \033[1;31m error \033[0m")
        dump_file.close()
        demo.kill()
        demo.wait()
        out_file.close()


if os.path.exists(dump_dir) != True:
    os.mkdir(dump_dir)

input_all_test_file(test_input_dir, test_output_dir)

print("This is a \033[1;35m test \033[0m!")
