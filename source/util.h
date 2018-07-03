// Utilities private to the library.

#include "anhttp/anhttp.h"

#include <netinet/in.h>

// Make a socket address out of the provided address and port args.
// Return an error if something bad happened.
AnhttpError_t anhttpMakeSocketAddress(const char *address,
        int port,
        struct sockaddr_in *sockAddr);
