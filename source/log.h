// Log a string and return the number of characters printed.
#define anhttpLog(format) _anhttpLogf(__FILE__, __LINE__, (format))

// Log something following the printf-format and return the number of characters
// printed.
#define anhttpLogf(format, ...) _anhttpLogf(__FILE__, __LINE__, (format), __VA_ARGS__)

int _anhttpLogf(const char *file, int line, const char *format, ...);
