#include "syscall.h"
#include <netinet/in.h>

// anhttpSocket
typedef struct {
    int domain;
    int type;
    int protocol;
} anhttpSocketArgs_t;
extern anhttpSocketArgs_t anhttpSocketArgs[];
extern int anhttpSocketArgsCount;
extern int anhttpSocketReturn;

// anhttpListen
typedef struct {
    int socket;
    int backlog;
} anhttpListenArgs_t;
extern anhttpListenArgs_t anhttpListenArgs[];
extern int anhttpListenArgsCount;
extern int anhttpListenReturn;

// anhttpClose
typedef struct {
    int fd;
} anhttpCloseArgs_t;
extern anhttpCloseArgs_t anhttpCloseArgs[];
extern int anhttpCloseArgsCount;
extern int anhttpCloseReturn;

// anhttpAccept
typedef struct {
    int fd;
    struct sockaddr address;
    socklen_t address_len;
} anhttpAcceptArgs_t;
extern anhttpAcceptArgs_t anhttpAcceptArgs[];
extern int anhttpAcceptArgsCount;
extern int anhttpAcceptReturn;

// anhttpBind
typedef struct {
    int socket;
    struct sockaddr address;
    socklen_t address_len;
} anhttpBindArgs_t;
extern anhttpBindArgs_t anhttpBindArgs[];
extern int anhttpBindArgsCount;
extern int anhttpBindReturn;

#define SYSCALL_STUBS_H_RESET() \
    anhttpSocketArgsCount = (int)0; \
    anhttpSocketReturn = (int)0; \
    anhttpListenArgsCount = (int)0; \
    anhttpListenReturn = (int)0; \
    anhttpCloseArgsCount = (int)0; \
    anhttpCloseReturn = (int)0; \
    anhttpAcceptArgsCount = (int)0; \
    anhttpAcceptReturn = (int)0; \
    anhttpBindArgsCount = (int)0; \
    anhttpBindReturn = (int)0; \
