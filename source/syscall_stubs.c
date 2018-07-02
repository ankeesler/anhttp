#include "syscall_stubs.h"

#include <assert.h>

// anhttpSocket
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

// anhttpListen
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

// anhttpClose
anhttpCloseArgs_t anhttpCloseArgs[64];
int anhttpCloseArgsCount = 0;
int anhttpCloseReturn = 0;
int anhttpClose(int fd) {
    if (anhttpCloseArgsCount == 64) assert(0);
    anhttpCloseArgs[anhttpCloseArgsCount].fd = fd;
    anhttpCloseArgsCount++;
    return anhttpCloseReturn;
}

// anhttpAccept
anhttpAcceptArgs_t anhttpAcceptArgs[64];
int anhttpAcceptArgsCount = 0;
int anhttpAcceptReturn = 0;
int anhttpAccept(int fd, struct sockaddr *address, socklen_t *address_len) {
    if (anhttpAcceptArgsCount == 64) assert(0);
    anhttpAcceptArgs[anhttpAcceptArgsCount].fd = fd;
    anhttpAcceptArgs[anhttpAcceptArgsCount].address = *address;
    anhttpAcceptArgs[anhttpAcceptArgsCount].address_len = *address_len;
    anhttpAcceptArgsCount++;
    return anhttpAcceptReturn;
}

// anhttpBind
anhttpBindArgs_t anhttpBindArgs[64];
int anhttpBindArgsCount = 0;
int anhttpBindReturn = 0;
int anhttpBind(int socket, const struct sockaddr *address, socklen_t address_len) {
    if (anhttpBindArgsCount == 64) assert(0);
    anhttpBindArgs[anhttpBindArgsCount].socket = socket;
    anhttpBindArgs[anhttpBindArgsCount].address = *address;
    anhttpBindArgs[anhttpBindArgsCount].address_len = address_len;
    anhttpBindArgsCount++;
    return anhttpBindReturn;
}

