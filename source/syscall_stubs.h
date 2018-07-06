#include "syscall.h"
#include <netinet/in.h>

// anhttpSocket
typedef int (*anhttpSocketFunction_t)(int domain, int type, int protocol);
typedef struct {
    int domain;
    int type;
    int protocol;
} anhttpSocketArgs_t;
extern anhttpSocketFunction_t anhttpSocketFunction;
extern anhttpSocketArgs_t anhttpSocketArgs[];
extern int anhttpSocketArgsCount;
extern int anhttpSocketReturn;

// anhttpListen
typedef int (*anhttpListenFunction_t)(int socket, int backlog);
typedef struct {
    int socket;
    int backlog;
} anhttpListenArgs_t;
extern anhttpListenFunction_t anhttpListenFunction;
extern anhttpListenArgs_t anhttpListenArgs[];
extern int anhttpListenArgsCount;
extern int anhttpListenReturn;

// anhttpClose
typedef int (*anhttpCloseFunction_t)(int fd);
typedef struct {
    int fd;
} anhttpCloseArgs_t;
extern anhttpCloseFunction_t anhttpCloseFunction;
extern anhttpCloseArgs_t anhttpCloseArgs[];
extern int anhttpCloseArgsCount;
extern int anhttpCloseReturn;

// anhttpAccept
typedef int (*anhttpAcceptFunction_t)(int fd, struct sockaddr* address, socklen_t* address_len);
typedef struct {
    int fd;
    struct sockaddr address;
    socklen_t address_len;
} anhttpAcceptArgs_t;
extern anhttpAcceptFunction_t anhttpAcceptFunction;
extern anhttpAcceptArgs_t anhttpAcceptArgs[];
extern int anhttpAcceptArgsCount;
extern int anhttpAcceptReturn;

// anhttpBind
typedef int (*anhttpBindFunction_t)(int socket, const struct sockaddr* address, socklen_t address_len);
typedef struct {
    int socket;
    struct sockaddr address;
    socklen_t address_len;
} anhttpBindArgs_t;
extern anhttpBindFunction_t anhttpBindFunction;
extern anhttpBindArgs_t anhttpBindArgs[];
extern int anhttpBindArgsCount;
extern int anhttpBindReturn;

#define SYSCALL_STUBS_H_RESET() \
    anhttpSocketFunction = (anhttpSocketFunction_t)0; \
    anhttpSocketArgsCount = (int)0; \
    anhttpSocketReturn = (int)0; \
    anhttpListenFunction = (anhttpListenFunction_t)0; \
    anhttpListenArgsCount = (int)0; \
    anhttpListenReturn = (int)0; \
    anhttpCloseFunction = (anhttpCloseFunction_t)0; \
    anhttpCloseArgsCount = (int)0; \
    anhttpCloseReturn = (int)0; \
    anhttpAcceptFunction = (anhttpAcceptFunction_t)0; \
    anhttpAcceptArgsCount = (int)0; \
    anhttpAcceptReturn = (int)0; \
    anhttpBindFunction = (anhttpBindFunction_t)0; \
    anhttpBindArgsCount = (int)0; \
    anhttpBindReturn = (int)0; \
