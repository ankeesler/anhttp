#include "thread_stubs.h"

#include <assert.h>

// anhttpThreadRun
anhttpThreadRunFunction_t anhttpThreadRunFunction = (anhttpThreadRunFunction_t)0;
anhttpThreadRunArgs_t anhttpThreadRunArgs[64];
int anhttpThreadRunArgsCount = 0;
AnhttpError_t anhttpThreadRunReturn = (AnhttpError_t)0;
AnhttpError_t anhttpThreadRun(anhttpThread_t *thread, anhttpThreadFunction_t function, void *input) {
    if (anhttpThreadRunArgsCount == 64) assert(0);
    anhttpThreadRunArgs[anhttpThreadRunArgsCount].thread = *thread;
    anhttpThreadRunArgs[anhttpThreadRunArgsCount].function = function;
    anhttpThreadRunArgs[anhttpThreadRunArgsCount].input = input;
    anhttpThreadRunArgsCount++;
    if (anhttpThreadRunFunction != (anhttpThreadRunFunction_t)0) return anhttpThreadRunFunction(thread, function, input);
    return anhttpThreadRunReturn;
}

// anhttpThreadWait
anhttpThreadWaitFunction_t anhttpThreadWaitFunction = (anhttpThreadWaitFunction_t)0;
anhttpThreadWaitArgs_t anhttpThreadWaitArgs[64];
int anhttpThreadWaitArgsCount = 0;
AnhttpError_t anhttpThreadWaitReturn = (AnhttpError_t)0;
AnhttpError_t anhttpThreadWait(anhttpThread_t *thread) {
    if (anhttpThreadWaitArgsCount == 64) assert(0);
    anhttpThreadWaitArgs[anhttpThreadWaitArgsCount].thread = *thread;
    anhttpThreadWaitArgsCount++;
    if (anhttpThreadWaitFunction != (anhttpThreadWaitFunction_t)0) return anhttpThreadWaitFunction(thread);
    return anhttpThreadWaitReturn;
}

// anhttpThreadCancel
anhttpThreadCancelFunction_t anhttpThreadCancelFunction = (anhttpThreadCancelFunction_t)0;
anhttpThreadCancelArgs_t anhttpThreadCancelArgs[64];
int anhttpThreadCancelArgsCount = 0;
AnhttpError_t anhttpThreadCancelReturn = (AnhttpError_t)0;
AnhttpError_t anhttpThreadCancel(anhttpThread_t *thread) {
    if (anhttpThreadCancelArgsCount == 64) assert(0);
    anhttpThreadCancelArgs[anhttpThreadCancelArgsCount].thread = *thread;
    anhttpThreadCancelArgsCount++;
    if (anhttpThreadCancelFunction != (anhttpThreadCancelFunction_t)0) return anhttpThreadCancelFunction(thread);
    return anhttpThreadCancelReturn;
}

