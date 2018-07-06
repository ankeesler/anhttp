#include "thread.h"
#include "anhttp/anhttp.h"
#include <pthread.h>

// anhttpThreadRun
typedef AnhttpError_t (*anhttpThreadRunFunction_t)(anhttpThread_t* thread, anhttpThreadFunction_t function, void* input);
typedef struct {
    anhttpThread_t thread;
    anhttpThreadFunction_t function;
    void* input;
} anhttpThreadRunArgs_t;
extern anhttpThreadRunFunction_t anhttpThreadRunFunction;
extern anhttpThreadRunArgs_t anhttpThreadRunArgs[];
extern int anhttpThreadRunArgsCount;
extern AnhttpError_t anhttpThreadRunReturn;

// anhttpThreadWait
typedef AnhttpError_t (*anhttpThreadWaitFunction_t)(anhttpThread_t* thread);
typedef struct {
    anhttpThread_t thread;
} anhttpThreadWaitArgs_t;
extern anhttpThreadWaitFunction_t anhttpThreadWaitFunction;
extern anhttpThreadWaitArgs_t anhttpThreadWaitArgs[];
extern int anhttpThreadWaitArgsCount;
extern AnhttpError_t anhttpThreadWaitReturn;

// anhttpThreadCancel
typedef AnhttpError_t (*anhttpThreadCancelFunction_t)(anhttpThread_t* thread);
typedef struct {
    anhttpThread_t thread;
} anhttpThreadCancelArgs_t;
extern anhttpThreadCancelFunction_t anhttpThreadCancelFunction;
extern anhttpThreadCancelArgs_t anhttpThreadCancelArgs[];
extern int anhttpThreadCancelArgsCount;
extern AnhttpError_t anhttpThreadCancelReturn;

#define THREAD_STUBS_H_RESET() \
    anhttpThreadRunFunction = (anhttpThreadRunFunction_t)0; \
    anhttpThreadRunArgsCount = (int)0; \
    anhttpThreadRunReturn = (AnhttpError_t)0; \
    anhttpThreadWaitFunction = (anhttpThreadWaitFunction_t)0; \
    anhttpThreadWaitArgsCount = (int)0; \
    anhttpThreadWaitReturn = (AnhttpError_t)0; \
    anhttpThreadCancelFunction = (anhttpThreadCancelFunction_t)0; \
    anhttpThreadCancelArgsCount = (int)0; \
    anhttpThreadCancelReturn = (AnhttpError_t)0; \
