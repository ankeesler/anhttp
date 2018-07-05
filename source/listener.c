#include "listener.h"

#include "anhttp/anhttp.h"

#include "syscall.h"
#include "log.h"
#include "util.h"

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

static void tryClose(int fd);

int anhttpCreateListener(const char *address, int port) {
    struct sockaddr_in listenSockAddr;
    AnhttpError_t error = anhttpMakeSocketAddress(address,
            port,
            &listenSockAddr);
    if (error != AnhttpErrorOK) {
        return -1;
    }

    int listenSock = anhttpSocket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == -1) {
        anhttpLog("Failed to create listen socket\n");
        return -1;
    }

    int err = anhttpBind(listenSock,
            (const struct sockaddr *)&listenSockAddr,
            sizeof(listenSockAddr));
    if (err == -1) {
        anhttpLog("Failed to bind socket to address: %s\n",
                AnhttpGetSystemError());
        tryClose(listenSock);
        return -1;
    }

    err = anhttpListen(listenSock, 0);
    if (err == -1) {
        anhttpLog("Failed to listen on socket: %s\n",
                AnhttpGetSystemError());
        tryClose(listenSock);
        return -1;
    }

    return listenSock;
}

int anhttpCloseListener(int listener) {
    return anhttpClose(listener);
}

static void tryClose(int fd) {
    if (anhttpCloseListener(fd) != -1) {
        anhttpLog("Failed to close fd %d: %s\n",
                fd,
                AnhttpGetSystemError());
    }
}
