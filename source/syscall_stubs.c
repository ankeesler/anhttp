#include "source/syscall_stubs.h"
#include "assert.h"
anhttpSocketArgs_t anhttpSocketArgs[64];
int anhttpSocketArgsCount = 0;
int anhttpSocketReturn = 0;
int anhttpSocket(int domain, int type, int protocol) {
    if (anhttpSocketArgsCount == 64) assert(0);
    anhttpSocketArgs[anhttpSocketArgsCount].domain = domain;
    anhttpSocketArgs[anhttpSocketArgsCount].type = type;
    anhttpSocketArgs[anhttpSocketArgsCount].protocol = protocol;
    anhttpSocketArgsCount++;
    return anhttpSocketReturn;
}

#include "assert.h"
anhttpListenArgs_t anhttpListenArgs[64];
int anhttpListenArgsCount = 0;
int anhttpListenReturn = 0;
int anhttpListen(int socket, int backlog) {
    if (anhttpListenArgsCount == 64) assert(0);
    anhttpListenArgs[anhttpListenArgsCount].socket = socket;
    anhttpListenArgs[anhttpListenArgsCount].backlog = backlog;
    anhttpListenArgsCount++;
    return anhttpListenReturn;
}

