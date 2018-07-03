#include "anhttp/anhttp.h"

#include "syscall.h"
#include "log.h"
#include "util.h"

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

    struct sockaddr_in listenSockAddr;
    AnhttpError_t error = anhttpMakeSocketAddress(server->address,
            server->port,
            &listenSockAddr);
    if (error != AnhttpErrorOK) {
        return error;
    }

    int listenSock = anhttpSocket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == -1) {
        anhttpLog("Failed to create listen socket\n");
        return AnhttpErrorSystem;
    }

    int err = anhttpBind(listenSock,
            (const struct sockaddr *)&listenSockAddr,
            sizeof(listenSockAddr));
    if (err == -1) {
        anhttpLog("Failed to bind socket to address: %s\n",
                AnhttpGetSystemError());
        tryClose(listenSock);
        return AnhttpErrorSystem;
    }
        
    err = anhttpListen(listenSock, 0);
    if (err == -1) {
        anhttpLog("Failed to listen on socket: %s\n",
                AnhttpGetSystemError());
        tryClose(listenSock);
        return AnhttpErrorSystem;
    }

    socklen_t listenSockAddrLen = sizeof(listenSockAddr);
    int connSock = anhttpAccept(listenSock,
            (struct sockaddr *)&listenSockAddr,
            &listenSockAddrLen);
    if (connSock == -1) {
        anhttpLog("Failed to accept on socket: %s\n",
                AnhttpGetSystemError());
        tryClose(listenSock);
        return AnhttpErrorSystem;
    }

    tryClose(listenSock);
    tryClose(connSock);

    return AnhttpErrorOK;
}
