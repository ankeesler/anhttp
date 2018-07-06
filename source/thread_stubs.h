#include "thread.h"
#include "anhttp/anhttp.h"
#include <pthread.h>

// anhttpThreadRun
typedef struct {
    anhttpThread_t thread;
    anhttpThreadFunction_t function;
    void* input;
} anhttpThreadRunArgs_t;
extern anhttpThreadRunArgs_t anhttpThreadRunArgs[];
extern int anhttpThreadRunArgsCount;
extern AnhttpError_t anhttpThreadRunReturn;

// anhttpThreadWait
typedef struct {
    anhttpThread_t thread;
} anhttpThreadWaitArgs_t;
extern anhttpThreadWaitArgs_t anhttpThreadWaitArgs[];
extern int anhttpThreadWaitArgsCount;
extern AnhttpError_t anhttpThreadWaitReturn;

// anhttpThreadCancel
typedef struct {
    anhttpThread_t thread;
} anhttpThreadCancelArgs_t;
extern anhttpThreadCancelArgs_t anhttpThreadCancelArgs[];
extern int anhttpThreadCancelArgsCount;
extern AnhttpError_t anhttpThreadCancelReturn;

#define THREAD_STUBS_H_RESET() \
    anhttpThreadRunArgsCount = (int)0; \
    anhttpThreadRunReturn = (AnhttpError_t)0; \
    anhttpThreadWaitArgsCount = (int)0; \
    anhttpThreadWaitReturn = (AnhttpError_t)0; \
    anhttpThreadCancelArgsCount = (int)0; \
    anhttpThreadCancelReturn = (AnhttpError_t)0; \
