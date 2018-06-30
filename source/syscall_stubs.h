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

