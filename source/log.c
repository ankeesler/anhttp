#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static const char *basename(const char *file);

int _anhttpLogf(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);

    printf("[anhttp:%s:%d]: ", basename(file), line);
    int printed = vprintf(format, args);
    fflush(stdout);

    va_end(args);

    return printed;
}

static const char *basename(const char *file) {
    int len = strlen(file);
    const char *ptr = file + len;
    for(; len > 0 && *ptr != '/'; len--, ptr--) {
        ;
    }
    return (len == 0 ? file : ptr+1);
}
