#include "anhttp/anhttp.h"

#include "unity.h"

#include "source/util.h"

#include "source/syscall_stubs.h"
#include "source/listener_stubs.h"
#include "source/connection_queue_stubs.h"
#include "source/thread_stubs.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

static void basicListeningSuccessTest(void) {
    SYSCALL_STUBS_H_RESET();
    LISTENER_STUBS_H_RESET();
    CONNECTION_QUEUE_STUBS_H_RESET();
    anhttpCreateListenerReturn = 5;
    anhttpStartListenerReturn = AnhttpErrorOK;
    anhttpConnectionQueueInitReturn = AnhttpErrorOK;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL(AnhttpErrorOK, error);

    TEST_ASSERT_EQUAL_INT(1, anhttpCreateListenerArgsCount);
    TEST_ASSERT_EQUAL_STRING(ANHTTP_SERVER_DEFAULT_ADDRESS,
            anhttpCreateListenerArgs[0].address);
    TEST_ASSERT_EQUAL_INT(ANHTTP_SERVER_DEFAULT_PORT,
            anhttpCreateListenerArgs[0].port);

    TEST_ASSERT_EQUAL_INT(1, anhttpConnectionQueueInitArgsCount);

    TEST_ASSERT_EQUAL_INT(1, anhttpStartListenerArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpStartListenerArgs[0].listener);

    TEST_ASSERT_EQUAL_INT(1, anhttpCloseListenerArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpCloseListenerArgs[0].listener);
}

static void nonDefaultAddressTest(void) {
    SYSCALL_STUBS_H_RESET();
    LISTENER_STUBS_H_RESET();
    anhttpCreateListenerReturn = 5;
    anhttpStartListenerReturn = AnhttpErrorOK;

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

    TEST_ASSERT_EQUAL_INT(1, anhttpStartListenerArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpStartListenerArgs[0].listener);

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

static void startListenerFailTest(void) {
    SYSCALL_STUBS_H_RESET();
    LISTENER_STUBS_H_RESET();
    anhttpCreateListenerReturn = 5;
    anhttpStartListenerReturn = AnhttpErrorSystem;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL(AnhttpErrorSystem, error);

    TEST_ASSERT_EQUAL_INT(1, anhttpCloseListenerArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpCloseListenerArgs[0].listener);
}

static AnhttpError_t connectionQueueRemoveFunction(anhttpConnectionQueue_t *q,
        anhttpConnection_t *connection) {
    static int call = 0;
    connection->fd = call + 6;
    return (call++ < 3 ? AnhttpErrorOK : AnhttpErrorSystem);
}

static void basicServingSuccessTest(void) {
    SYSCALL_STUBS_H_RESET();
    LISTENER_STUBS_H_RESET();
    CONNECTION_QUEUE_STUBS_H_RESET();
    THREAD_STUBS_H_RESET();
    anhttpCreateListenerReturn = 5;
    anhttpStartListenerReturn = AnhttpErrorOK;
    anhttpConnectionQueueRemoveFunction = connectionQueueRemoveFunction;
    anhttpConnectionQueueInitReturn = AnhttpErrorOK;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL(AnhttpErrorOK, error);

    TEST_ASSERT_EQUAL_INT(3, anhttpCloseArgsCount);
    TEST_ASSERT_EQUAL_INT(6, anhttpCloseArgs[0].fd);
    TEST_ASSERT_EQUAL_INT(7, anhttpCloseArgs[1].fd);
    TEST_ASSERT_EQUAL_INT(8, anhttpCloseArgs[2].fd);

    TEST_ASSERT_EQUAL_INT(1, anhttpThreadCancelArgsCount);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();

    // Listening
    RUN_TEST(basicListeningSuccessTest);
    RUN_TEST(nonDefaultAddressTest);
    RUN_TEST(createListenerFailTest);
    RUN_TEST(startListenerFailTest);

    // Serving
    RUN_TEST(basicServingSuccessTest);

    return UNITY_END();
}
