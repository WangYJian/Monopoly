import os
import io

old_dir_input = "test_file/group_2_test/input"
old_dir_output = "./test_file/group_2_test/output"
old_dir_out = "./test_file/group_2_test/old"

def write_files(in_file:io.TextIOWrapper, out_file:io.TextIOWrapper):
    out_file.write(in_file.read())

def modify_old(input_dir, output_dir):
    if os.path.exists(old_dir_out) != True:
        os.mkdir(old_dir_out)
    in_dirs = os.listdir(input_dir)
    print(in_dirs)
    for dir in in_dirs:
        if os.path.isdir(input_dir+"/"+dir) != True:
            continue
        in_files = os.listdir(input_dir+"/"+dir)
        sorted(in_files)
        out_files = os.listdir(output_dir+"/"+dir)
        sorted(out_files)
        old_input_path = input_dir+"/"+dir
        old_output_path = output_dir+"/"+dir
        for cnt in range(len(in_files)):
            new_path = old_dir_out+"/"+dir+"_{pos}".format(pos=cnt)
            os.makedirs(new_path)
            case_input = open(new_path+"/input", "w+", encoding="utf-8")
            case_output = open(new_path+"/output", "w+", encoding="utf-8")
            old_input = open(old_input_path+"/case_{pos}".format(pos=cnt), "r", encoding="utf-8")
            old_output = open(old_output_path+"/case_{pos}".format(pos=cnt), "r",encoding="utf-8")
            write_files(old_input, case_input)
            write_files(old_output, case_output)

modify_old(old_dir_input, old_dir_output)      
        