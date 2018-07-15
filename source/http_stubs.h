#include "http.h"
#include "anhttp/anhttp.h"
#include <stddef.h>

// anhttpParseHttpRequest
typedef AnhttpError_t (*anhttpParseHttpRequestFunction_t)(AnhttpRequest_t* req, void* buf, size_t buf_len);
typedef struct {
    AnhttpRequest_t req;
    void* buf;
    size_t buf_len;
} anhttpParseHttpRequestArgs_t;
extern anhttpParseHttpRequestFunction_t anhttpParseHttpRequestFunction;
extern anhttpParseHttpRequestArgs_t anhttpParseHttpRequestArgs[];
extern int anhttpParseHttpRequestArgsCount;
extern AnhttpError_t anhttpParseHttpRequestReturn;

#define HTTP_STUBS_H_RESET() \
    anhttpParseHttpRequestFunction = (anhttpParseHttpRequestFunction_t)0; \
    anhttpParseHttpRequestArgsCount = (int)0; \
    anhttpParseHttpRequestReturn = (AnhttpError_t)0; \
