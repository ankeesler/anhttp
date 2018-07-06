#ifndef __THREAD_H__
#define __THREAD_H__

// This is a generic thread interface.

#include "anhttp/anhttp.h"

#include <pthread.h>

// These threads are implemented via pthreads.
typedef struct {
    pthread_t pthread;
} anhttpThread_t;

typedef void *(*anhttpThreadFunction_t)(void *);

// Run a function in a thread.
// Returns whether or not this was successful.
AnhttpError_t anhttpThreadRun(anhttpThread_t *thread,
        anhttpThreadFunction_t function,
        void *input);

// Wait for a thread to return.
AnhttpError_t anhttpThreadWait(anhttpThread_t *thread);

// Cancel a thread.
AnhttpError_t anhttpThreadCancel(anhttpThread_t *thread);

#endif // ifdef __THREAD_H__
