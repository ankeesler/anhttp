#include "anhttp/anhttp.h"

#include "syscall.h"

#include <sys/socket.h>

AnhttpError_t ListenAndServe(AnhttpServer_t *server) {
    int sock = anhttpSocket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return AnhttpErrorSystem;
    }

    int err = anhttpListen(sock, 0);
    (void)err;

    return AnhttpErrorOK;
}
