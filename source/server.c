#include "anhttp/anhttp.h"

#include "syscall.h"
#include "log.h"
#include "listener.h"

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

static void tryClose(int fd) {
    int err = anhttpClose(fd);
    if (err == -1) {
        anhttpLog("Failed to close fd %d: %s\n",
                AnhttpGetSystemError());
    }
}

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

    struct sockaddr_in connSockAddr;
    socklen_t connSockAddrLen;
    int connSock = anhttpAccept(listener,
            (struct sockaddr *)&connSockAddr,
            &connSockAddrLen);
    if (connSock == -1) {
        anhttpLog("Failed to accept on socket: %s\n",
                AnhttpGetSystemError());
        tryClose(listener);
        return AnhttpErrorSystem;
    }

    if (anhttpCloseListener(listener) == -1) {
        anhttpLog("Failed to close listener: %s\n",
                AnhttpGetSystemError());
    }
    tryClose(connSock);

    return AnhttpErrorOK;
}
