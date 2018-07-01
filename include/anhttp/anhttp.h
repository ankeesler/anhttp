// Errors.
typedef const char *AnhttpError_t;
// Everything is OK.
extern AnhttpError_t AnhttpErrorOK;
// An error occurred in a syscall. Use AnhttpGetSystemError for the actual system
// error.
extern AnhttpError_t AnhttpErrorSystem;
// An address was invalid.
extern AnhttpError_t AnhttpErrorAddress;

// Get the actual system error associated with a AnhttpErrorSystem return.
const char *AnhttpGetSystemError(void);

// The default address that a server will listen on.
#define ANHTTP_SERVER_DEFAULT_ADDRESS "127.0.0.1"
// The default port that a server will listen on.
#define ANHTTP_SERVER_DEFAULT_PORT 12345

// This is an HTTP server.
//
// To initialize this struct to all defaults, simply set all fields to 0.
typedef struct {
    // The address on which the server listens. When this is NULL, the address
    // is set to ANHTTP_SERVER_DEFAULT_ADDRESS.
    const char *address;
    // The port on which the server listen. When this is 0, the port is set to
    // ANHTTP_SERVER_DEFAULT_PORT.
    int port;
} AnhttpServer_t;

// Start listening for requests on this server.
AnhttpError_t AnhttpListenAndServe(AnhttpServer_t *server);
