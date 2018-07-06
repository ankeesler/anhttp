#include "syscall_stubs.h"

#include <assert.h>

// anhttpSocket
anhttpSocketFunction_t anhttpSocketFunction = (anhttpSocketFunction_t)0;
anhttpSocketArgs_t anhttpSocketArgs[64];
int anhttpSocketArgsCount = 0;
int anhttpSocketReturn = (int)0;
int anhttpSocket(int domain, int type, int protocol) {
    if (anhttpSocketArgsCount == 64) assert(0);
    anhttpSocketArgs[anhttpSocketArgsCount].domain = domain;
    anhttpSocketArgs[anhttpSocketArgsCount].type = type;
    anhttpSocketArgs[anhttpSocketArgsCount].protocol = protocol;
    anhttpSocketArgsCount++;
    if (anhttpSocketFunction != (anhttpSocketFunction_t)0) return anhttpSocketFunction(domain, type, protocol);
    return anhttpSocketReturn;
}

// anhttpListen
anhttpListenFunction_t anhttpListenFunction = (anhttpListenFunction_t)0;
anhttpListenArgs_t anhttpListenArgs[64];
int anhttpListenArgsCount = 0;
int anhttpListenReturn = (int)0;
int anhttpListen(int socket, int backlog) {
    if (anhttpListenArgsCount == 64) assert(0);
    anhttpListenArgs[anhttpListenArgsCount].socket = socket;
    anhttpListenArgs[anhttpListenArgsCount].backlog = backlog;
    anhttpListenArgsCount++;
    if (anhttpListenFunction != (anhttpListenFunction_t)0) return anhttpListenFunction(socket, backlog);
    return anhttpListenReturn;
}

// anhttpClose
anhttpCloseFunction_t anhttpCloseFunction = (anhttpCloseFunction_t)0;
anhttpCloseArgs_t anhttpCloseArgs[64];
int anhttpCloseArgsCount = 0;
int anhttpCloseReturn = (int)0;
int anhttpClose(int fd) {
    if (anhttpCloseArgsCount == 64) assert(0);
    anhttpCloseArgs[anhttpCloseArgsCount].fd = fd;
    anhttpCloseArgsCount++;
    if (anhttpCloseFunction != (anhttpCloseFunction_t)0) return anhttpCloseFunction(fd);
    return anhttpCloseReturn;
}

// anhttpAccept
anhttpAcceptFunction_t anhttpAcceptFunction = (anhttpAcceptFunction_t)0;
anhttpAcceptArgs_t anhttpAcceptArgs[64];
int anhttpAcceptArgsCount = 0;
int anhttpAcceptReturn = (int)0;
int anhttpAccept(int fd, struct sockaddr *address, socklen_t *address_len) {
    if (anhttpAcceptArgsCount == 64) assert(0);
    anhttpAcceptArgs[anhttpAcceptArgsCount].fd = fd;
    anhttpAcceptArgs[anhttpAcceptArgsCount].address = *address;
    anhttpAcceptArgs[anhttpAcceptArgsCount].address_len = *address_len;
    anhttpAcceptArgsCount++;
    if (anhttpAcceptFunction != (anhttpAcceptFunction_t)0) return anhttpAcceptFunction(fd, address, address_len);
    return anhttpAcceptReturn;
}

// anhttpBind
anhttpBindFunction_t anhttpBindFunction = (anhttpBindFunction_t)0;
anhttpBindArgs_t anhttpBindArgs[64];
int anhttpBindArgsCount = 0;
int anhttpBindReturn = (int)0;
int anhttpBind(int socket, const struct sockaddr *address, socklen_t address_len) {
    if (anhttpBindArgsCount == 64) assert(0);
    anhttpBindArgs[anhttpBindArgsCount].socket = socket;
    anhttpBindArgs[anhttpBindArgsCount].address = *address;
    anhttpBindArgs[anhttpBindArgsCount].address_len = address_len;
    anhttpBindArgsCount++;
    if (anhttpBindFunction != (anhttpBindFunction_t)0) return anhttpBindFunction(socket, address, address_len);
    return anhttpBindReturn;
}

