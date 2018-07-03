#include "thread.h"

#include "anhttp/anhttp.h"

#include <pthread.h>
#include <errno.h>

AnhttpError_t anhttpThreadRun(anhttpThread_t *thread, anhttpThreadFunction_t function, void *input) {
    int err = pthread_create(&thread->pthread, NULL, function, input);
    if (err != 0) {
        errno = err;
        return AnhttpErrorSystem;
    }
    return AnhttpErrorOK;
}

AnhttpError_t anhttpThreadWait(anhttpThread_t *thread) {
    int err = pthread_join(thread->pthread, NULL);
    if (err != 0) {
        errno = err;
        return AnhttpErrorSystem;
    }
    return AnhttpErrorOK;
}

AnhttpError_t anhttpThreadCancel(anhttpThread_t *thread) {
    int err = pthread_cancel(thread->pthread);
    if (err != 0) {
        errno = err;
        return AnhttpErrorSystem;
    }
    return AnhttpErrorOK;
}
