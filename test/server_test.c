#include "anhttp/anhttp.h"

#include "unity.h"

#include "source/util.h"

#include "source/syscall_stubs.h"
#include "source/listener_stubs.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

static void successTest(void) {
    SYSCALL_STUBS_H_RESET();
    LISTENER_STUBS_H_RESET();
    anhttpCreateListenerReturn = 5;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL(AnhttpErrorOK, error);

    TEST_ASSERT_EQUAL_INT(1, anhttpCreateListenerArgsCount);
    TEST_ASSERT_EQUAL_STRING(ANHTTP_SERVER_DEFAULT_ADDRESS,
            anhttpCreateListenerArgs[0].address);
    TEST_ASSERT_EQUAL_INT(ANHTTP_SERVER_DEFAULT_PORT,
            anhttpCreateListenerArgs[0].port);

    TEST_ASSERT_EQUAL_INT(1, anhttpCloseListenerArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpCloseListenerArgs[0].listener);
}

static void nonDefaultAddressTest(void) {
    SYSCALL_STUBS_H_RESET();
    LISTENER_STUBS_H_RESET();
    anhttpCreateListenerReturn = 5;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    server.address = "127.0.0.1";
    server.port = 4477;
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL(AnhttpErrorOK, error);

    TEST_ASSERT_EQUAL_INT(1, anhttpCreateListenerArgsCount);
    TEST_ASSERT_EQUAL_STRING("127.0.0.1",
            anhttpCreateListenerArgs[0].address);
    TEST_ASSERT_EQUAL_INT(4477,
            anhttpCreateListenerArgs[0].port);

    TEST_ASSERT_EQUAL_INT(1, anhttpAcceptArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpAcceptArgs[0].fd);

    TEST_ASSERT_EQUAL_INT(1, anhttpCloseListenerArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpCloseListenerArgs[0].listener);
}

static void createListenerFailTest(void) {
    SYSCALL_STUBS_H_RESET();
    LISTENER_STUBS_H_RESET();
    anhttpCreateListenerReturn = -1;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorSystem, error);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(successTest);
    RUN_TEST(nonDefaultAddressTest);
    RUN_TEST(createListenerFailTest);
    return UNITY_END();
}
