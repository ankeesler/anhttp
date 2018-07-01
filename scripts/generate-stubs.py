#!/usr/bin/python

import sys

def generate_c_file(line, name, args, file_lines):
    if len(args) > 0:
        file_lines += "%sArgs_t %sArgs[64];\n" % (name, name)
    file_lines += "int %sArgsCount = 0;\n" % (name)
    file_lines += "int %sReturn = 0;\n" % (name)
    file_lines += line + "\n"
    file_lines += "    if (%sArgsCount == 64) assert(0);\n" % (name)
    for arg in args:
        field = arg[1]
        if field[0] == "*":
            field = field[1:]
        rvalue = arg[1]
        if arg[0] == "char":
            rvalue = "(char *)" + rvalue[1:]
        file_lines += "    %sArgs[%sArgsCount].%s = %s;\n" % (name, name, field, rvalue)
    file_lines += "    %sArgsCount++;\n" % (name)
    file_lines += "    return %sReturn;\n" % (name)
    file_lines += "}\n"
    file_lines += "\n"

def generate_h_file(line, name, args, file_lines):
    file_lines += "\n"
    if len(args) > 0:
        file_lines += "typedef struct {\n"
        for arg in args:
            field = arg[1]
            if field[0] == "*" and arg[0] != "char":
                field = field[1:]
            file_lines += "    %s %s;\n" % (arg[0], field)
        file_lines += "} %sArgs_t;\n" % (name)
        file_lines += "extern %sArgs_t %sArgs[];\n" % (name, name)
    file_lines += "extern int %sArgsCount;\n" % (name)
    file_lines += "extern int %sReturn;\n" % (name)
    file_lines += "\n"

def get_args(line, name):
    """Returns an array of tuples of the form (type, name)"""
    if "()" in line:
        return []

    start_args = len("int ") + len(name) + 1
    end_args = line.find(")")
    args = line[start_args:end_args]

    ret = []
    for arg in args.split(","):
        arg = arg.strip()
        split = arg.split(" ")
        if split[0] == "const":
            split = split[1:]
        if len(split) == 3: # struct sockaddr *addr
            split[0] = " ".join(split[0:2])
            split[1] = split[2]
        ret.append((split[0], split[1]))

    return ret

def get_name(line):
    name_start = len("int ")
    name_end = line.find("(")
    name = line[name_start:name_end]
    return name

def process_func(line, c_file_lines, h_file_lines):
    name = get_name(line)
    args = get_args(line, name)
    generate_c_file(line, name, args, c_file_lines)
    generate_h_file(line, name, args, h_file_lines)

def main():
    if len(sys.argv) < 2:
        print "usage: %s path/to/source/file"  % (sys.argv[0])
        exit(1)

    c_file_lines = []
    h_file_lines = []
    with open(sys.argv[1]) as f:
        for line in f:
            line = line.strip()
            if "int anhttp" in line:
                process_func(line, c_file_lines, h_file_lines)

    h_file = sys.argv[1][:-2] + "_stubs.h"
    with open(h_file, "w") as f:
        f.write("#include <netinet/in.h>\n")
        for line in h_file_lines:
            f.write(line)

    c_file = sys.argv[1][:-2] + "_stubs.c"
    with open(c_file, "w") as f:
        f.write("#include \"%s\"\n" % (h_file))
        f.write("#include \"assert.h\"\n")
        f.write("\n")
        for line in c_file_lines:
            f.write(line)

if __name__ == "__main__":
    main()
