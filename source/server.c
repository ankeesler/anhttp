#include "anhttp/anhttp.h"

#include "syscall.h"
#include "log.h"

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

    struct sockaddr_in listenSockAddr;
    memset(&listenSockAddr, 0, sizeof(listenSockAddr));
    listenSockAddr.sin_len = sizeof(listenSockAddr);
    listenSockAddr.sin_family = AF_INET;
    listenSockAddr.sin_port = htons(server->port);
    switch (inet_pton(AF_INET, server->address, &listenSockAddr.sin_addr)) {
        case 0:
            return AnhttpErrorAddress;
        case -1:
            return AnhttpErrorSystem;
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
        anhttpLog("Failed to bind socket to address\n");
        anhttpClose(listenSock); // TODO: log error!
        return AnhttpErrorSystem;
    }
        
    err = anhttpListen(listenSock, 0);
    if (err == -1) {
        anhttpLog("Failed to listen on socket\n");
        anhttpClose(listenSock); // TODO: log error!
        return AnhttpErrorSystem;
    }

    socklen_t listenSockAddrLen = sizeof(listenSockAddr);
    int connSock = anhttpAccept(listenSock,
            (struct sockaddr *)&listenSockAddr,
            &listenSockAddrLen);
    if (connSock == -1) {
        anhttpLog("Failed to accept socket connection\n");
        anhttpClose(listenSock); // TODO: log error!
        return AnhttpErrorSystem;
    }

    anhttpClose(listenSock);  // TODO: log error!
    anhttpClose(connSock);  // TODO: log error!

    return AnhttpErrorOK;
}
