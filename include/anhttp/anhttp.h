// Anhttp master header.

#ifndef __ANHTTP_H__
#define __ANHTTP_H__

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

#define ANHTTP_METHOD_GET "GET"
#define ANHTTP_METHOD_POST "POST"
#define ANHTTP_METHOD_PUT "PUT"
#define ANHTTP_METHOD_DELETE "DELETE"

// This is an HTTP request.
typedef struct {
    // "GET", "POST", "PUT", "DELETE", etc.
    const char *method;
    const char *uri;
    // headers...
    unsigned char *payload;
    int payloadLen;
} AnhttpRequest_t;

#define ANHTTP_STATUS_OK 200
#define ANHTTP_STATUS_NO_CONTENT 204

typedef struct {
    int status;
    // headers...
    unsigned char *payload;
    int payloadLen;
} AnhttpResponse_t;

// This is a function that handles an HTTP request.
// When this function is called, the rsp argument is set to defaults.
// Implementations of this method should assign the fields of the response
// to their liking.
typedef void (*AnhttpHandler)(AnhttpResponse_t *rsp, const AnhttpRequest_t *req);

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
    // The handler to be called when an HTTP request is recieved.
    // If this is NULL, the requests will simply be printed to stdout.
    AnhttpHandler handler;
} AnhttpServer_t;

// Start listening for requests on this server.
AnhttpError_t AnhttpListenAndServe(AnhttpServer_t *server);

#endif // ifdef __ANHTTP_H__
