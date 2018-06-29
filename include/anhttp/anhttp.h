// Errors.
typedef const char *AnhttpError_t;
extern AnhttpError_t AnhttpErrorOK;

// This is an HTTP server.
typedef struct {
    // The address on which the server listens.
    const char *address;
} AnhttpServer_t;
