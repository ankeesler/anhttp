#!/usr/bin/python

import os
import pprint
import re
import sys

class FileParser:
    """This is the thing that does the parsing of the header file."""
    def __init__(self, stub_file):
        self.stub_file = stub_file

    def parse(self, lines):
        """This function parses the lines of a file and populates its stub_file field."""
        function_lines = []
        for line in lines:
            line = line.strip()

            if len(function_lines) > 0:
                function_lines.append(line)
            elif not line.startswith("typedef") and "(" in line:
                function_lines.append(line)
            elif line.startswith("#include"):
                include = line[len("#include "):]
                self.stub_file.add_include(include)

            if not line.startswith("typedef") and line.endswith(");"):
                real_line = " ".join(function_lines)
                m = re.match("(\\w+) (\\w+)\(([a-zA-Z0-9,_ *]+)\);", real_line)
                if not m:
                    raise Exception("cannot parse function name out of %s" % (real_line))
                return_type = m.group(1)
                name = m.group(2)
                args = self.__parse_args(m.group(3))
                function = Function(real_line, name, return_type, args)
                self.stub_file.add_function(function)
                function_lines = []

    def __parse_args(self, line):
        args = []
        for arg in line.split(","):
            args.append(self.__parse_arg(arg))
        return args

    def __parse_arg(self, line):
        line = line.strip()
        last_space = line.rfind(" ")
        if last_space == -1:
            raise Exception("cannot find space in arg line: %s" % (line))
        name = line[last_space+1:]
        teyep = line[:last_space]
        if name[0] == "*":
            teyep += "*"
            name = name[1:]
        return Arg(teyep, name)

class StubFile:
    def __init__(self):
        self.includes = []
        self.functions = []

    def __str__(self):
        s = ""
        s += "includes: %s\n" % (self.includes)
        s += "functions: %s\n" % ([f.__str__() for f in self.functions])
        return s

    def add_include(self, include):
        self.includes.append(include)

    def add_function(self, function):
        self.functions.append(function)

class Function:
    def __init__(self, line, name, return_type, args):
        self.line = line
        self.name = name
        self.return_type = return_type
        self.args = args

    def __str__(self):
        return "name: %s, return_type: %s, args: %s" % (self.name, self.return_type, [a.__str__() for a in self.args])

class Arg:
    def __init__(self, teyep, name):
        self.teyep = teyep
        self.name = name

    def __str__(self):
        return "teyep: %s, name: %s" % (self.teyep, self.name)

    def is_const(self):
        return self.teyep.startswith("const")

    def is_pointer(self):
        return self.teyep.endswith("*")

    def is_string(self):
        return self.teyep == "const char*"

    def is_voidstar(self):
        return self.teyep == "void*" or self.teyep == "const void*"

    def cleaned_type(self):
        teyep = self.teyep
        if not self.is_string() and not self.is_voidstar():
            if self.is_const():
                teyep = teyep[len("const "):]
            if self.is_pointer():
                teyep = teyep[:-1]
        return teyep

def make_function_type_call(function):
    s = ""
    s += function.name + "Function"
    s += "("
    for i in range(len(function.args)):
        arg = function.args[i]
        if i != 0:
            s += ", "
        s += arg.name
    s += ")"
    return s

def function_type_name(function):
    return function.name + "Function_t"

def make_function_type(function):
    s = ""
    s += function.return_type + " "
    s += "(*" + function_type_name(function) + ")"
    if len(function.args) > 0:
        s += "("
        for i in range(len(function.args)):
            arg = function.args[i]
            if i != 0:
                s += ", "
            s += arg.teyep + " " + arg.name
        s += ")"
    else:
        s += "(void)"
    s += ";"
    return s

def write_h_file(f, stub_file):
    f.write("#include \"%s\"\n" % (os.path.basename(f.name).replace("_stubs", "")))
    for include in stub_file.includes:
        f.write("#include %s\n" % (include))
    f.write("\n")

    state = [] # (variable_name, variable_type)
    for function in stub_file.functions:
        f.write("// %s\n" % (function.name))
        f.write("typedef %s\n" % make_function_type(function))
        f.write("typedef struct {\n")
        for arg in function.args:
            f.write("    %s %s;\n" % (arg.cleaned_type(), arg.name))
        f.write("} %sArgs_t;\n" % (function.name))
        f.write("extern %s %sFunction;\n" % (function_type_name(function), function.name))
        state.append(("%sFunction" % (function.name), function_type_name(function)))
        f.write("extern %sArgs_t %sArgs[];\n" % (function.name, function.name))
        f.write("extern int %sArgsCount;\n" % (function.name))
        state.append(("%sArgsCount" % (function.name), "int"))
        if function.return_type != "void":
            f.write("extern %s %sReturn;\n" % (function.return_type, function.name))
            state.append(("%sReturn" % (function.name), function.return_type))
        f.write("\n")

    file_name = os.path.basename(f.name).replace(".", "_").upper()
    f.write("#define %s_RESET() \\\n" % file_name)
    [f.write("    %s = (%s)0; \\\n" % (s[0], s[1])) for s in state]

def write_c_file(f, stub_file):
    h_file_name = os.path.basename(f.name).replace(".c", ".h")
    f.write("#include \"%s\"\n" % (h_file_name))
    f.write("\n")
    f.write("#include <assert.h>\n")
    f.write("\n")

    for function in stub_file.functions:
        f.write("// %s\n" % (function.name))
        f.write("%s %sFunction = (%s)0;\n" % (function_type_name(function), function.name, function_type_name(function)))
        f.write("%sArgs_t %sArgs[64];\n" % (function.name, function.name))
        f.write("int %sArgsCount = 0;\n" % (function.name))
        if function.return_type != "void":
            f.write("%s %sReturn = (%s)0;\n" % (function.return_type, function.name, function.return_type))
        f.write("%s {\n" % (function.line.replace(";", "")))
        f.write("    if (%sArgsCount == 64) assert(0);\n" % function.name)
        for arg in function.args:
            rvalue = arg.name
            if arg.is_pointer() and not arg.is_string() and not arg.is_voidstar():
                rvalue = "*" + rvalue
            f.write("    %sArgs[%sArgsCount].%s = %s;\n" % (function.name, function.name, arg.name, rvalue))
        f.write("    %sArgsCount++;\n" % (function.name))
        if function.return_type != "void":
            f.write("    if (%sFunction != (%s)0) return %s;\n" % (function.name, function_type_name(function), make_function_type_call(function)))
            f.write("    return %sReturn;\n" % (function.name))
        else:
            f.write("    if (%sFunction != (%s)0) %s;\n" % (function.name, function_type_name(function), make_function_type_call(function)))
        f.write("}\n")
        f.write("\n")

def main():
    if len(sys.argv) < 4:
        print "usage: %s <path/to/header_file.h> <header_file_stubs.h> <header_file_stubs.c>"  % (sys.argv[0])
        exit(1)

    h_file_name = sys.argv[1]
    generated_h_file_name = sys.argv[2]
    generated_c_file_name = sys.argv[3]

    lines = []
    with open(h_file_name) as f:
        [lines.append(line) for line in f]

    stub_file = StubFile()
    file_parser = FileParser(stub_file)
    file_parser.parse(lines)

    with open(generated_h_file_name, "w") as f:
        write_h_file(f, stub_file)

    with open(generated_c_file_name, "w") as f:
        write_c_file(f, stub_file)

if __name__ == "__main__":
    main()
