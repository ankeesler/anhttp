#include "anhttp/anhttp.h"

#include "syscall.h"
#include "log.h"
#include "listener.h"

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

AnhttpError_t AnhttpListenAndServe(AnhttpServer_t *server) {
    if (server->address == NULL) {
        server->address = ANHTTP_SERVER_DEFAULT_ADDRESS;
    }

    if (server->port == 0) {
        server->port = ANHTTP_SERVER_DEFAULT_PORT;
    }

    int listener = anhttpCreateListener(server->address, server->port);
    if (listener == -1) {
        return AnhttpErrorSystem;
    }

    anhttpThread_t listenerThread;
    anhttpConnectionQueue_t connectionQ;
    AnhttpError_t error = anhttpStartListener(listener,
            &listenerThread,
            &connectionQ);
    if (error != AnhttpErrorOK) {
        anhttpLog("Failed to start listener: %s\n", AnhttpGetSystemError());
        if (anhttpCloseListener(listener) == -1) {
            anhttpLog("Failed to close listener: %s\n", AnhttpGetSystemError());
        }
        return AnhttpErrorSystem;
    }

    if (anhttpCloseListener(listener) == -1) {
        anhttpLog("Failed to close listener: %s\n",
                AnhttpGetSystemError());
    }

    return AnhttpErrorOK;
}
