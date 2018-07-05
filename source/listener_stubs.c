#include "listener_stubs.h"

#include <assert.h>

// anhttpCreateListener
anhttpCreateListenerArgs_t anhttpCreateListenerArgs[64];
int anhttpCreateListenerArgsCount = 0;
int anhttpCreateListenerReturn = 0;
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
int anhttpCloseListenerReturn = 0;
int anhttpCloseListener(int listener) {
    if (anhttpCloseListenerArgsCount == 64) assert(0);
    anhttpCloseListenerArgs[anhttpCloseListenerArgsCount].listener = listener;
    anhttpCloseListenerArgsCount++;
    return anhttpCloseListenerReturn;
}

