#include "anhttp/anhttp.h"

#include <string.h>
#include <errno.h>

AnhttpError_t AnhttpErrorOK = "OK";
AnhttpError_t AnhttpErrorSystem = "System";
AnhttpError_t AnhttpErrorAddress = "Address";

const char *AnhttpGetSystemError(void) {
    return strerror(errno);
}
