#include "util.h"

#include "anhttp/anhttp.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

AnhttpError_t anhttpMakeSocketAddress(const char *address,
        int port,
        struct sockaddr_in *sockAddr) {
    memset(sockAddr, 0, sizeof(*sockAddr));
    sockAddr->sin_len = sizeof(*sockAddr);
    sockAddr->sin_family = AF_INET;
    sockAddr->sin_port = htons(port);
    switch (inet_pton(AF_INET, address, &sockAddr->sin_addr)) {
        case 0:
            return AnhttpErrorAddress;
        case -1:
            return AnhttpErrorSystem;
        default:
            return AnhttpErrorOK;
    }
}
