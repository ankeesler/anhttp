#include "listener.h"
#include "anhttp/anhttp.h"
#include "thread.h"
#include "connection_queue.h"

// anhttpCreateListener
typedef int (*anhttpCreateListenerFunction_t)(const char* address, int port);
typedef struct {
    const char* address;
    int port;
} anhttpCreateListenerArgs_t;
extern anhttpCreateListenerFunction_t anhttpCreateListenerFunction;
extern anhttpCreateListenerArgs_t anhttpCreateListenerArgs[];
extern int anhttpCreateListenerArgsCount;
extern int anhttpCreateListenerReturn;

// anhttpCloseListener
typedef int (*anhttpCloseListenerFunction_t)(int listener);
typedef struct {
    int listener;
} anhttpCloseListenerArgs_t;
extern anhttpCloseListenerFunction_t anhttpCloseListenerFunction;
extern anhttpCloseListenerArgs_t anhttpCloseListenerArgs[];
extern int anhttpCloseListenerArgsCount;
extern int anhttpCloseListenerReturn;

// anhttpStartListener
typedef AnhttpError_t (*anhttpStartListenerFunction_t)(int listener, anhttpThread_t* thread, anhttpConnectionQueue_t* connectionQ);
typedef struct {
    int listener;
    anhttpThread_t thread;
    anhttpConnectionQueue_t connectionQ;
} anhttpStartListenerArgs_t;
extern anhttpStartListenerFunction_t anhttpStartListenerFunction;
extern anhttpStartListenerArgs_t anhttpStartListenerArgs[];
extern int anhttpStartListenerArgsCount;
extern AnhttpError_t anhttpStartListenerReturn;

#define LISTENER_STUBS_H_RESET() \
    anhttpCreateListenerFunction = (anhttpCreateListenerFunction_t)0; \
    anhttpCreateListenerArgsCount = (int)0; \
    anhttpCreateListenerReturn = (int)0; \
    anhttpCloseListenerFunction = (anhttpCloseListenerFunction_t)0; \
    anhttpCloseListenerArgsCount = (int)0; \
    anhttpCloseListenerReturn = (int)0; \
    anhttpStartListenerFunction = (anhttpStartListenerFunction_t)0; \
    anhttpStartListenerArgsCount = (int)0; \
    anhttpStartListenerReturn = (AnhttpError_t)0; \
