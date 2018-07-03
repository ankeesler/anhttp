#include "connection_queue.h"

#include <unistd.h>
#include <assert.h>
#include <errno.h>

#define PIPE_READ_FD 0
#define PIPE_WRITE_FD 1

static AnhttpError_t lock(anhttpConnectionQueue_t *q);
static AnhttpError_t unlock(anhttpConnectionQueue_t *q);

AnhttpError_t anhttpConnectionQueueInit(anhttpConnectionQueue_t *q) {
    if (pipe(q->pipeFds) == -1) {
        return AnhttpErrorSystem;
    }

    q->length = 0;

    int err = pthread_mutex_init(&q->mutex, NULL);
    if (err != 0) {
        errno = err;
        return AnhttpErrorSystem;
    }

    return AnhttpErrorOK;
}

void anhttpConnectionQueueFree(anhttpConnectionQueue_t *q) {
    close(q->pipeFds[PIPE_READ_FD]);
    close(q->pipeFds[PIPE_WRITE_FD]);

    q->length = 0;

    pthread_mutex_destroy(&q->mutex);
}

AnhttpError_t anhttpConnectionQueueAdd(anhttpConnectionQueue_t *q,
        anhttpConnection_t *connection) {
    AnhttpError_t error = lock(q);
    if (error != AnhttpErrorOK) {
        return error;
    }

    int writeCount = write(q->pipeFds[PIPE_WRITE_FD],
            connection,
            sizeof(anhttpConnection_t));
    if (writeCount == -1) {
        unlock(q);
        return AnhttpErrorSystem;
    } else if (writeCount < sizeof(anhttpConnection_t)) {
        assert(0); // :(
    }

    q->length++;

    error = unlock(q);
    if (error != AnhttpErrorOK) {
        return error;
    }

    return AnhttpErrorOK;
}

AnhttpError_t anhttpConnectionQueueRemove(anhttpConnectionQueue_t *q,
        anhttpConnection_t *connection) {
    AnhttpError_t error = lock(q);
    if (error != AnhttpErrorOK) {
        return error;
    }

    int readCount = read(q->pipeFds[PIPE_READ_FD],
            connection,
            sizeof(anhttpConnection_t));
    if (readCount == -1) {
        return AnhttpErrorSystem;
    } else if (readCount < sizeof(anhttpConnection_t)) {
        assert(0); // :(
    }

    q->length--;

    error = unlock(q);
    if (error != AnhttpErrorOK) {
        return error;
    }

    return AnhttpErrorOK;
}

AnhttpError_t anhttpConnectionQueueLength(anhttpConnectionQueue_t *q,
        int *length) {
    AnhttpError_t error = lock(q);
    if (error != AnhttpErrorOK) {
        return error;
    }

    *length = q->length;

    error = unlock(q);
    if (error != AnhttpErrorOK) {
        return error;
    }

    return AnhttpErrorOK;
}

static AnhttpError_t lock(anhttpConnectionQueue_t *q) {
    int err = pthread_mutex_lock(&q->mutex);
    if (err != 0) {
        errno = err;
        return AnhttpErrorSystem;
    }
    return AnhttpErrorOK;
}

static AnhttpError_t unlock(anhttpConnectionQueue_t *q) {
    int err = pthread_mutex_unlock(&q->mutex);
    if (err != 0) {
        errno = err;
        return AnhttpErrorSystem;
    }
    return AnhttpErrorOK;
}

