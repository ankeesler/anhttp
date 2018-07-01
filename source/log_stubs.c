#include "source/log_stubs.h"
#include "assert.h"

anhttpLogArgs_t anhttpLogArgs[64];
int anhttpLogArgsCount = 0;
int anhttpLogReturn = 0;
int anhttpLog(const char *string) {
    if (anhttpLogArgsCount == 64) assert(0);
    anhttpLogArgs[anhttpLogArgsCount].string = (char *)string;
    anhttpLogArgsCount++;
    return anhttpLogReturn;
}

