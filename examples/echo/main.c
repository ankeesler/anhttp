#include "anhttp/anhttp.h"

#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));

    printf("Starting server on address %s:%d...\n",
            ANHTTP_SERVER_DEFAULT_ADDRESS,
            ANHTTP_SERVER_DEFAULT_PORT);
    AnhttpError_t error = AnhttpListenAndServe(&server);
    printf("ListenAndServe returned: %s\n", error);

    return 0;
}
