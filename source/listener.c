#include "listener.h"

#include "anhttp/anhttp.h"

#include "syscall.h"
#include "log.h"
#include "util.h"
#include "thread.h"
#include "connection_queue.h"

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define RUN_LISTENER_INPUT_MARK 0xAC12ACAB

typedef struct {
    int mark;
    int listener;
    anhttpConnectionQueue_t *connectionQ;
} runListenerInput_t;

static void tryClose(int fd);
static void *runListener(void *);
static void failListener(runListenerInput_t *input);

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

AnhttpError_t anhttpStartListener(int listener,
        anhttpThread_t *thread,
        anhttpConnectionQueue_t *connectionQ) {
    static runListenerInput_t input;
    input.mark = RUN_LISTENER_INPUT_MARK;
    input.listener = listener;
    input.connectionQ = connectionQ;
    return anhttpThreadRun(thread, runListener, &input);
}

static void tryClose(int fd) {
    if (anhttpCloseListener(fd) != -1) {
        anhttpLog("Failed to close fd %d: %s\n",
                fd,
                AnhttpGetSystemError());
    }
}

static void *runListener(void *data) {
    runListenerInput_t *input = (runListenerInput_t *)data;

    if (input->mark != RUN_LISTENER_INPUT_MARK) {
        anhttpLog("Expected 0x%08X run listener mark, got 0x%08X\n",
                RUN_LISTENER_INPUT_MARK,
                input->mark);
        failListener(input);
        return NULL;
    }

    anhttpLog("Running listener on fd %d\n", input->listener);
    while (1) {
        struct sockaddr_in sockAddr;
        socklen_t sockAddrLen;
        int connSock = anhttpAccept(input->listener,
                (struct sockaddr *)&sockAddr,
                &sockAddrLen);
        if (connSock == -1) {
            anhttpLog("Failure in accept() call: %s\n",
                    AnhttpGetSystemError());
            failListener(input);
            break;
        }

        anhttpLog("Accepted connection from XXX, connSock = %d\n",
                connSock);

        anhttpConnection_t connection = {
            .fd = connSock,
        };
        AnhttpError_t error
            = anhttpConnectionQueueAdd(input->connectionQ, &connection);
        if (error != AnhttpErrorOK) {
            anhttpLog("Failed to write fd %d to connection queue\n",
                    connSock);
        }
    }

    return NULL;
}

static void failListener(runListenerInput_t *input) {
    anhttpConnection_t failure = {
        .fd = -1,
    };
    AnhttpError_t error = anhttpConnectionQueueAdd(input->connectionQ,
            &failure);
    if (error != AnhttpErrorOK) {
        anhttpLog("Failed to write failure to connection queue\n");
    }
}
