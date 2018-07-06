#include "thread_stubs.h"

#include <assert.h>

// anhttpThreadRun
anhttpThreadRunArgs_t anhttpThreadRunArgs[64];
int anhttpThreadRunArgsCount = 0;
AnhttpError_t anhttpThreadRunReturn = (AnhttpError_t)0;
AnhttpError_t anhttpThreadRun(anhttpThread_t *thread, anhttpThreadFunction_t function, void *input) {
    if (anhttpThreadRunArgsCount == 64) assert(0);
    anhttpThreadRunArgs[anhttpThreadRunArgsCount].thread = *thread;
    anhttpThreadRunArgs[anhttpThreadRunArgsCount].function = function;
    anhttpThreadRunArgs[anhttpThreadRunArgsCount].input = input;
    anhttpThreadRunArgsCount++;
    return anhttpThreadRunReturn;
}

// anhttpThreadWait
anhttpThreadWaitArgs_t anhttpThreadWaitArgs[64];
int anhttpThreadWaitArgsCount = 0;
AnhttpError_t anhttpThreadWaitReturn = (AnhttpError_t)0;
AnhttpError_t anhttpThreadWait(anhttpThread_t *thread) {
    if (anhttpThreadWaitArgsCount == 64) assert(0);
    anhttpThreadWaitArgs[anhttpThreadWaitArgsCount].thread = *thread;
    anhttpThreadWaitArgsCount++;
    return anhttpThreadWaitReturn;
}

// anhttpThreadCancel
anhttpThreadCancelArgs_t anhttpThreadCancelArgs[64];
int anhttpThreadCancelArgsCount = 0;
AnhttpError_t anhttpThreadCancelReturn = (AnhttpError_t)0;
AnhttpError_t anhttpThreadCancel(anhttpThread_t *thread) {
    if (anhttpThreadCancelArgsCount == 64) assert(0);
    anhttpThreadCancelArgs[anhttpThreadCancelArgsCount].thread = *thread;
    anhttpThreadCancelArgsCount++;
    return anhttpThreadCancelReturn;
}

