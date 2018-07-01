#include <netinet/in.h>

typedef struct {
    int domain;
    int type;
    int protocol;
} anhttpSocketArgs_t;
extern anhttpSocketArgs_t anhttpSocketArgs[];
extern int anhttpSocketArgsCount;
extern int anhttpSocketReturn;


typedef struct {
    int socket;
    int backlog;
} anhttpListenArgs_t;
extern anhttpListenArgs_t anhttpListenArgs[];
extern int anhttpListenArgsCount;
extern int anhttpListenReturn;


typedef struct {
    int fd;
} anhttpCloseArgs_t;
extern anhttpCloseArgs_t anhttpCloseArgs[];
extern int anhttpCloseArgsCount;
extern int anhttpCloseReturn;


typedef struct {
    int fd;
    struct sockaddr address;
    socklen_t address_len;
} anhttpAcceptArgs_t;
extern anhttpAcceptArgs_t anhttpAcceptArgs[];
extern int anhttpAcceptArgsCount;
extern int anhttpAcceptReturn;


typedef struct {
    int socket;
    struct sockaddr address;
    socklen_t address_len;
} anhttpBindArgs_t;
extern anhttpBindArgs_t anhttpBindArgs[];
extern int anhttpBindArgsCount;
extern int anhttpBindReturn;

