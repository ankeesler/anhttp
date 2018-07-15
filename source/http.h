// HTTP related stuff, like packet parsing.

#include "anhttp/anhttp.h"

#include <stddef.h>

AnhttpError_t anhttpParseHttpRequest(AnhttpRequest_t *req, void *buf, size_t buf_len);
