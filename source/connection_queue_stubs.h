#include "connection_queue.h"
#include "anhttp/anhttp.h"
#include <pthread.h>

// anhttpConnectionQueueInit
typedef AnhttpError_t (*anhttpConnectionQueueInitFunction_t)(anhttpConnectionQueue_t* q);
typedef struct {
    anhttpConnectionQueue_t q;
} anhttpConnectionQueueInitArgs_t;
extern anhttpConnectionQueueInitFunction_t anhttpConnectionQueueInitFunction;
extern anhttpConnectionQueueInitArgs_t anhttpConnectionQueueInitArgs[];
extern int anhttpConnectionQueueInitArgsCount;
extern AnhttpError_t anhttpConnectionQueueInitReturn;

// anhttpConnectionQueueFree
typedef void (*anhttpConnectionQueueFreeFunction_t)(anhttpConnectionQueue_t* q);
typedef struct {
    anhttpConnectionQueue_t q;
} anhttpConnectionQueueFreeArgs_t;
extern anhttpConnectionQueueFreeFunction_t anhttpConnectionQueueFreeFunction;
extern anhttpConnectionQueueFreeArgs_t anhttpConnectionQueueFreeArgs[];
extern int anhttpConnectionQueueFreeArgsCount;

// anhttpConnectionQueueAdd
typedef AnhttpError_t (*anhttpConnectionQueueAddFunction_t)(anhttpConnectionQueue_t* q, anhttpConnection_t* connection);
typedef struct {
    anhttpConnectionQueue_t q;
    anhttpConnection_t connection;
} anhttpConnectionQueueAddArgs_t;
extern anhttpConnectionQueueAddFunction_t anhttpConnectionQueueAddFunction;
extern anhttpConnectionQueueAddArgs_t anhttpConnectionQueueAddArgs[];
extern int anhttpConnectionQueueAddArgsCount;
extern AnhttpError_t anhttpConnectionQueueAddReturn;

// anhttpConnectionQueueRemove
typedef AnhttpError_t (*anhttpConnectionQueueRemoveFunction_t)(anhttpConnectionQueue_t* q, anhttpConnection_t* connection);
typedef struct {
    anhttpConnectionQueue_t q;
    anhttpConnection_t connection;
} anhttpConnectionQueueRemoveArgs_t;
extern anhttpConnectionQueueRemoveFunction_t anhttpConnectionQueueRemoveFunction;
extern anhttpConnectionQueueRemoveArgs_t anhttpConnectionQueueRemoveArgs[];
extern int anhttpConnectionQueueRemoveArgsCount;
extern AnhttpError_t anhttpConnectionQueueRemoveReturn;

// anhttpConnectionQueueLength
typedef AnhttpError_t (*anhttpConnectionQueueLengthFunction_t)(anhttpConnectionQueue_t* q, int* length);
typedef struct {
    anhttpConnectionQueue_t q;
    int length;
} anhttpConnectionQueueLengthArgs_t;
extern anhttpConnectionQueueLengthFunction_t anhttpConnectionQueueLengthFunction;
extern anhttpConnectionQueueLengthArgs_t anhttpConnectionQueueLengthArgs[];
extern int anhttpConnectionQueueLengthArgsCount;
extern AnhttpError_t anhttpConnectionQueueLengthReturn;

#define CONNECTION_QUEUE_STUBS_H_RESET() \
    anhttpConnectionQueueInitFunction = (anhttpConnectionQueueInitFunction_t)0; \
    anhttpConnectionQueueInitArgsCount = (int)0; \
    anhttpConnectionQueueInitReturn = (AnhttpError_t)0; \
    anhttpConnectionQueueFreeFunction = (anhttpConnectionQueueFreeFunction_t)0; \
    anhttpConnectionQueueFreeArgsCount = (int)0; \
    anhttpConnectionQueueAddFunction = (anhttpConnectionQueueAddFunction_t)0; \
    anhttpConnectionQueueAddArgsCount = (int)0; \
    anhttpConnectionQueueAddReturn = (AnhttpError_t)0; \
    anhttpConnectionQueueRemoveFunction = (anhttpConnectionQueueRemoveFunction_t)0; \
    anhttpConnectionQueueRemoveArgsCount = (int)0; \
    anhttpConnectionQueueRemoveReturn = (AnhttpError_t)0; \
    anhttpConnectionQueueLengthFunction = (anhttpConnectionQueueLengthFunction_t)0; \
    anhttpConnectionQueueLengthArgsCount = (int)0; \
    anhttpConnectionQueueLengthReturn = (AnhttpError_t)0; \
