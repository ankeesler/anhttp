#include "http.h"

#include "anhttp/anhttp.h"

#include <stddef.h>

AnhttpError_t anhttpParseHttpRequest(AnhttpRequest_t *req,
        void *buf,
        size_t buf_len) {
    return AnhttpErrorOK;
}
