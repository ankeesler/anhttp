#include "http_stubs.h"

#include <assert.h>

// anhttpParseHttpRequest
anhttpParseHttpRequestFunction_t anhttpParseHttpRequestFunction = (anhttpParseHttpRequestFunction_t)0;
anhttpParseHttpRequestArgs_t anhttpParseHttpRequestArgs[64];
int anhttpParseHttpRequestArgsCount = 0;
AnhttpError_t anhttpParseHttpRequestReturn = (AnhttpError_t)0;
AnhttpError_t anhttpParseHttpRequest(AnhttpRequest_t *req, void *buf, size_t buf_len) {
    if (anhttpParseHttpRequestArgsCount == 64) assert(0);
    anhttpParseHttpRequestArgs[anhttpParseHttpRequestArgsCount].req = *req;
    anhttpParseHttpRequestArgs[anhttpParseHttpRequestArgsCount].buf = buf;
    anhttpParseHttpRequestArgs[anhttpParseHttpRequestArgsCount].buf_len = buf_len;
    anhttpParseHttpRequestArgsCount++;
    if (anhttpParseHttpRequestFunction != (anhttpParseHttpRequestFunction_t)0) return anhttpParseHttpRequestFunction(req, buf, buf_len);
    return anhttpParseHttpRequestReturn;
}

