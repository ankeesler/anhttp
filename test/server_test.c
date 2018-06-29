#include "anhttp/anhttp.h"

#include "unity.h"

#include <assert.h>

static void basicTest(void) {
    AnhttpServer_t server;
    AnhttpError_t error = ListenAndServe(&server);
    TEST_ASSERT_EQUAL(error, AnhttpErrorOK);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(basicTest);
    return UNITY_END();
}
