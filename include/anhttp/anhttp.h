// Errors.
typedef const char *AnhttpError_t;
extern AnhttpError_t AnhttpErrorOK;
extern AnhttpError_t AnhttpErrorSystem;

// This is an HTTP server.
//
// To initialize this struct to all defaults, simply set all fields to 0.
typedef struct {
    // The address on which the server listens.
    const char *address;
} AnhttpServer_t;

// Start listening for requests on this server.
AnhttpError_t ListenAndServe(AnhttpServer_t *server);
