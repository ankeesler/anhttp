// Errors.
typedef const char *AnhttpError;
extern AnhttpError AnhttpErrorOK;

// This is an HTTP server.
typedef struct AnhttpServer {
    // The address on which the server listens.
    const char *address;
};
