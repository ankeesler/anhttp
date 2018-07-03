// This is a thread-safe, blocking queue that contains connections
// established by a listener.

#include "anhttp/anhttp.h"

#include <pthread.h>

typedef struct {
    int fd;
    // address
    // time
} anhttpConnection_t;

// The queue is implemented via an os pipe.
typedef struct {
    int pipeFds[2];
    int length;
    pthread_mutex_t mutex;
} anhttpConnectionQueue_t;

// Initialize a queue.
AnhttpError_t anhttpConnectionQueueInit(anhttpConnectionQueue_t *q);

// Free the resources associated with a queue.
void anhttpConnectionQueueFree(anhttpConnectionQueue_t *q);

// Add something to the queue.
// Copies the provided connection into the queue.
AnhttpError_t anhttpConnectionQueueAdd(anhttpConnectionQueue_t *q,
        anhttpConnection_t *connection);

// Remove something from the queue.
// Returns AnhttpErrorOK if something was actually removed.
// Blocks until there is something on the queue. This is a "smart"
// block, i.e., the system will do other stuff will it blocks.
// Copies the returned connection to the provided pointer.
AnhttpError_t anhttpConnectionQueueRemove(anhttpConnectionQueue_t *q,
        anhttpConnection_t *connection);

// Get the number of elements in the queue.
// Writes the length to the provided length pointer.
AnhttpError_t anhttpConnectionQueueLength(anhttpConnectionQueue_t *q,
        int *length);
