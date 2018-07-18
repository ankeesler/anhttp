#include "anhttp/anhttp.h"

#include "syscall.h"
#include "log.h"
#include "listener.h"
#include "http.h"

#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

static void serve(AnhttpServer_t *server,
        anhttpThread_t *listenerThread,
        anhttpConnectionQueue_t *connectionQueue);
static void handleConnection(AnhttpServer_t *server, int fd);

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
    anhttpLogf("Server created listener %d\n", listener);

    anhttpThread_t listenerThread;

    anhttpConnectionQueue_t connectionQ;
    AnhttpError_t error = anhttpConnectionQueueInit(&connectionQ);
    if (error != AnhttpErrorOK) {
        anhttpLogf("Failed to initialize connection queue: %s\n",
                AnhttpGetSystemError());
        return AnhttpErrorSystem;
    }
    anhttpLog("Initalized connection queue\n");

    error = anhttpStartListener(listener, &listenerThread, &connectionQ);
    if (error != AnhttpErrorOK) {
        anhttpLogf("Failed to start listener: %s\n", AnhttpGetSystemError());
        if (anhttpCloseListener(listener) == -1) {
            anhttpLogf("Failed to close listener: %s\n", AnhttpGetSystemError());
        }
        return AnhttpErrorSystem;
    }
    anhttpLogf("Server started listener %d\n", listener);

    serve(server, &listenerThread, &connectionQ);

    if (anhttpCloseListener(listener) == -1) {
        anhttpLogf("Failed to close listener: %s\n",
                AnhttpGetSystemError());
    } else {
        anhttpLogf("Closed listener %d\n", listener);
    }

    anhttpLog("Server exiting\n");
    return AnhttpErrorOK;
}

static void serve(AnhttpServer_t *server,
        anhttpThread_t *listenerThread,
        anhttpConnectionQueue_t *connectionQ) {
    while (1) {
        anhttpConnection_t connection;
        AnhttpError_t error = anhttpConnectionQueueRemove(connectionQ, &connection);
        if (error != AnhttpErrorOK) {
            anhttpLogf("Failed to removed from connection queue: %s (maybe: %s)\n",
                    error,
                    AnhttpGetSystemError());
            break;
        }

        anhttpLogf("Removed connection from connection queue: %d\n", connection.fd);

        handleConnection(server, connection.fd);

        if (anhttpClose(connection.fd) == -1) {
            anhttpLogf("Failed to close connection %d: %s\n",
                    connection.fd,
                    AnhttpGetSystemError());
        } else {
            anhttpLogf("Closing connection fd %d\n", connection.fd);
        }
    }

    AnhttpError_t error = anhttpThreadCancel(listenerThread);
    if (error != AnhttpErrorOK) {
        anhttpLogf("Failed to cancel listener thread: %s\n",
                AnhttpGetSystemError());
    } else {
        anhttpLog("Cancelled listener thread\n");
    }
}

static void handleConnection(AnhttpServer_t *server, int fd) {
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    ssize_t readCount = anhttpRead(fd, buffer, sizeof(buffer));
    anhttpLogf("read %ld bytes\n", readCount);
    anhttpLogf("Received %s\n", buffer);

    AnhttpRequest_t req;
    memset(&req, 0, sizeof(req));
    AnhttpError_t error = anhttpParseHttpRequest(&req,
            buffer,
            readCount);
    (void)error;

    AnhttpResponse_t rsp;
    memset(&rsp, 0, sizeof(rsp));
    rsp.status = ANHTTP_STATUS_OK;
    if (server->handler != NULL) {
        server->handler(&rsp, &req);
    } else {
        anhttpLog("Server does not contain handler\n");
    }

    ssize_t writeCount = anhttpWrite(fd, rsp.payload, rsp.payloadLen);
    anhttpLogf("wrote %ld bytes\n", writeCount);
}
