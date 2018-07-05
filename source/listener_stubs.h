#include "anhttp/anhttp.h"
#include "thread.h"
#include "connection_queue.h"

// anhttpCreateListener
typedef struct {
    const char* address;
    int port;
} anhttpCreateListenerArgs_t;
extern anhttpCreateListenerArgs_t anhttpCreateListenerArgs[];
extern int anhttpCreateListenerArgsCount;
extern int anhttpCreateListenerReturn;

// anhttpCloseListener
typedef struct {
    int listener;
} anhttpCloseListenerArgs_t;
extern anhttpCloseListenerArgs_t anhttpCloseListenerArgs[];
extern int anhttpCloseListenerArgsCount;
extern int anhttpCloseListenerReturn;

#define LISTENER_STUBS_H_RESET() \
    anhttpCreateListenerArgsCount = 0; \
    anhttpCreateListenerReturn = 0; \
    anhttpCloseListenerArgsCount = 0; \
    anhttpCloseListenerReturn = 0; \
