#include "connection_queue_stubs.h"

#include <assert.h>

// anhttpConnectionQueueInit
anhttpConnectionQueueInitFunction_t anhttpConnectionQueueInitFunction = (anhttpConnectionQueueInitFunction_t)0;
anhttpConnectionQueueInitArgs_t anhttpConnectionQueueInitArgs[64];
int anhttpConnectionQueueInitArgsCount = 0;
AnhttpError_t anhttpConnectionQueueInitReturn = (AnhttpError_t)0;
AnhttpError_t anhttpConnectionQueueInit(anhttpConnectionQueue_t *q) {
    if (anhttpConnectionQueueInitArgsCount == 64) assert(0);
    anhttpConnectionQueueInitArgs[anhttpConnectionQueueInitArgsCount].q = *q;
    anhttpConnectionQueueInitArgsCount++;
    if (anhttpConnectionQueueInitFunction != (anhttpConnectionQueueInitFunction_t)0) return anhttpConnectionQueueInitFunction(q);
    return anhttpConnectionQueueInitReturn;
}

// anhttpConnectionQueueFree
anhttpConnectionQueueFreeFunction_t anhttpConnectionQueueFreeFunction = (anhttpConnectionQueueFreeFunction_t)0;
anhttpConnectionQueueFreeArgs_t anhttpConnectionQueueFreeArgs[64];
int anhttpConnectionQueueFreeArgsCount = 0;
void anhttpConnectionQueueFree(anhttpConnectionQueue_t *q) {
    if (anhttpConnectionQueueFreeArgsCount == 64) assert(0);
    anhttpConnectionQueueFreeArgs[anhttpConnectionQueueFreeArgsCount].q = *q;
    anhttpConnectionQueueFreeArgsCount++;
    if (anhttpConnectionQueueFreeFunction != (anhttpConnectionQueueFreeFunction_t)0) anhttpConnectionQueueFreeFunction(q);
}

// anhttpConnectionQueueAdd
anhttpConnectionQueueAddFunction_t anhttpConnectionQueueAddFunction = (anhttpConnectionQueueAddFunction_t)0;
anhttpConnectionQueueAddArgs_t anhttpConnectionQueueAddArgs[64];
int anhttpConnectionQueueAddArgsCount = 0;
AnhttpError_t anhttpConnectionQueueAddReturn = (AnhttpError_t)0;
AnhttpError_t anhttpConnectionQueueAdd(anhttpConnectionQueue_t *q, anhttpConnection_t *connection) {
    if (anhttpConnectionQueueAddArgsCount == 64) assert(0);
    anhttpConnectionQueueAddArgs[anhttpConnectionQueueAddArgsCount].q = *q;
    anhttpConnectionQueueAddArgs[anhttpConnectionQueueAddArgsCount].connection = *connection;
    anhttpConnectionQueueAddArgsCount++;
    if (anhttpConnectionQueueAddFunction != (anhttpConnectionQueueAddFunction_t)0) return anhttpConnectionQueueAddFunction(q, connection);
    return anhttpConnectionQueueAddReturn;
}

// anhttpConnectionQueueRemove
anhttpConnectionQueueRemoveFunction_t anhttpConnectionQueueRemoveFunction = (anhttpConnectionQueueRemoveFunction_t)0;
anhttpConnectionQueueRemoveArgs_t anhttpConnectionQueueRemoveArgs[64];
int anhttpConnectionQueueRemoveArgsCount = 0;
AnhttpError_t anhttpConnectionQueueRemoveReturn = (AnhttpError_t)0;
AnhttpError_t anhttpConnectionQueueRemove(anhttpConnectionQueue_t *q, anhttpConnection_t *connection) {
    if (anhttpConnectionQueueRemoveArgsCount == 64) assert(0);
    anhttpConnectionQueueRemoveArgs[anhttpConnectionQueueRemoveArgsCount].q = *q;
    anhttpConnectionQueueRemoveArgs[anhttpConnectionQueueRemoveArgsCount].connection = *connection;
    anhttpConnectionQueueRemoveArgsCount++;
    if (anhttpConnectionQueueRemoveFunction != (anhttpConnectionQueueRemoveFunction_t)0) return anhttpConnectionQueueRemoveFunction(q, connection);
    return anhttpConnectionQueueRemoveReturn;
}

// anhttpConnectionQueueLength
anhttpConnectionQueueLengthFunction_t anhttpConnectionQueueLengthFunction = (anhttpConnectionQueueLengthFunction_t)0;
anhttpConnectionQueueLengthArgs_t anhttpConnectionQueueLengthArgs[64];
int anhttpConnectionQueueLengthArgsCount = 0;
AnhttpError_t anhttpConnectionQueueLengthReturn = (AnhttpError_t)0;
AnhttpError_t anhttpConnectionQueueLength(anhttpConnectionQueue_t *q, int *length) {
    if (anhttpConnectionQueueLengthArgsCount == 64) assert(0);
    anhttpConnectionQueueLengthArgs[anhttpConnectionQueueLengthArgsCount].q = *q;
    anhttpConnectionQueueLengthArgs[anhttpConnectionQueueLengthArgsCount].length = *length;
    anhttpConnectionQueueLengthArgsCount++;
    if (anhttpConnectionQueueLengthFunction != (anhttpConnectionQueueLengthFunction_t)0) return anhttpConnectionQueueLengthFunction(q, length);
    return anhttpConnectionQueueLengthReturn;
}

