#include <stdio.h>
#include <stdarg.h>

int anhttpLog(const char *format, ...) {
    va_list args;
    va_start(args, format);

    printf("[anhttp]: ");
    int printed = vprintf(format, args);
    fflush(stdout);

    va_end(args);

    return printed;
}
