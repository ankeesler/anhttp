#include "listener_stubs.h"

#include <assert.h>

// anhttpCreateListener
anhttpCreateListenerArgs_t anhttpCreateListenerArgs[64];
int anhttpCreateListenerArgsCount = 0;
int anhttpCreateListenerReturn = (int)0;
int anhttpCreateListener(const char *address, int port) {
    if (anhttpCreateListenerArgsCount == 64) assert(0);
    anhttpCreateListenerArgs[anhttpCreateListenerArgsCount].address = address;
    anhttpCreateListenerArgs[anhttpCreateListenerArgsCount].port = port;
    anhttpCreateListenerArgsCount++;
    return anhttpCreateListenerReturn;
}

// anhttpCloseListener
anhttpCloseListenerArgs_t anhttpCloseListenerArgs[64];
int anhttpCloseListenerArgsCount = 0;
int anhttpCloseListenerReturn = (int)0;
int anhttpCloseListener(int listener) {
    if (anhttpCloseListenerArgsCount == 64) assert(0);
    anhttpCloseListenerArgs[anhttpCloseListenerArgsCount].listener = listener;
    anhttpCloseListenerArgsCount++;
    return anhttpCloseListenerReturn;
}

// anhttpStartListener
anhttpStartListenerArgs_t anhttpStartListenerArgs[64];
int anhttpStartListenerArgsCount = 0;
AnhttpError_t anhttpStartListenerReturn = (AnhttpError_t)0;
AnhttpError_t anhttpStartListener(int listener, anhttpThread_t *thread, anhttpConnectionQueue_t *connectionQ) {
    if (anhttpStartListenerArgsCount == 64) assert(0);
    anhttpStartListenerArgs[anhttpStartListenerArgsCount].listener = listener;
    anhttpStartListenerArgs[anhttpStartListenerArgsCount].thread = *thread;
    anhttpStartListenerArgs[anhttpStartListenerArgsCount].connectionQ = *connectionQ;
    anhttpStartListenerArgsCount++;
    return anhttpStartListenerReturn;
}

