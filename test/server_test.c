#include "anhttp/anhttp.h"

#include "unity.h"

#include "source/syscall_stubs.h"

#include <sys/socket.h>

static void successTest(void) {
    anhttpSocketReturn = 5;
    anhttpListenReturn = 0;

    AnhttpServer_t server;
    AnhttpError_t error = ListenAndServe(&server);
    TEST_ASSERT_EQUAL(error, AnhttpErrorOK);

    TEST_ASSERT_EQUAL_INT(anhttpSocketArgsCount, 1);
    TEST_ASSERT_EQUAL_INT(anhttpSocketArgs[0].domain, AF_INET);
    TEST_ASSERT_EQUAL_INT(anhttpSocketArgs[0].type, SOCK_STREAM);
    TEST_ASSERT_EQUAL_INT(anhttpSocketArgs[0].protocol, 0);

    TEST_ASSERT_EQUAL_INT(anhttpListenArgsCount, 1);
    TEST_ASSERT_EQUAL_INT(anhttpListenArgs[0].socket, 5);
    TEST_ASSERT_EQUAL_INT(anhttpListenArgs[0].backlog, 0);
}

static void socketFailureTest(void) {
    anhttpSocketReturn = -1;

    AnhttpServer_t server;
    AnhttpError_t error = ListenAndServe(&server);
    TEST_ASSERT_EQUAL_STRING(error, AnhttpErrorSystem);

}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(successTest);
    RUN_TEST(socketFailureTest);
    return UNITY_END();
}
