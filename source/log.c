#include <stdio.h>
#include <stdarg.h>

int anhttpLog(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int printed = vprintf(format, args);

    va_end(args);

    return printed;
}
