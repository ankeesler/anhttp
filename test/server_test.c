#include "anhttp/anhttp.h"

#include "unity.h"

#include "source/syscall_stubs.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

static void successTest(void) {
    SYSCALL_STUBS_H_RESET();
    anhttpSocketReturn = 5;
    anhttpAcceptReturn = 6;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL(AnhttpErrorOK, error);

    TEST_ASSERT_EQUAL_INT(1, anhttpSocketArgsCount);
    TEST_ASSERT_EQUAL_INT(AF_INET, anhttpSocketArgs[0].domain);
    TEST_ASSERT_EQUAL_INT(SOCK_STREAM, anhttpSocketArgs[0].type);
    TEST_ASSERT_EQUAL_INT(0, anhttpSocketArgs[0].protocol);

    struct sockaddr_in expectedAddr;
    memset(&expectedAddr, 0, sizeof(expectedAddr));
    expectedAddr.sin_len = sizeof(expectedAddr);
    expectedAddr.sin_family = AF_INET;
    expectedAddr.sin_port = htons(ANHTTP_SERVER_DEFAULT_PORT);
    TEST_ASSERT_EQUAL_INT(1,
            inet_pton(AF_INET,
                ANHTTP_SERVER_DEFAULT_ADDRESS,
                &expectedAddr.sin_addr));

    TEST_ASSERT_EQUAL_INT(1, anhttpBindArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpBindArgs[0].socket);
    TEST_ASSERT_EQUAL_MEMORY(&expectedAddr,
            &anhttpBindArgs[0].address,
            sizeof(expectedAddr));
    TEST_ASSERT_EQUAL(sizeof(expectedAddr), anhttpBindArgs[0].address_len);

    TEST_ASSERT_EQUAL_INT(1, anhttpListenArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpListenArgs[0].socket);
    TEST_ASSERT_EQUAL_INT(0, anhttpListenArgs[0].backlog);

    TEST_ASSERT_EQUAL_INT(1, anhttpAcceptArgsCount);
    TEST_ASSERT_EQUAL_MEMORY(&expectedAddr,
            &anhttpAcceptArgs[0].address,
            sizeof(expectedAddr));
    TEST_ASSERT_EQUAL(sizeof(expectedAddr), anhttpAcceptArgs[0].address_len);

    TEST_ASSERT_EQUAL_INT(2, anhttpCloseArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpCloseArgs[0].fd);
    TEST_ASSERT_EQUAL_INT(6, anhttpCloseArgs[1].fd);
}

static void nonDefaultAddressTest(void) {
    anhttpSocketArgsCount = 0;
    anhttpBindArgsCount = 0;
    anhttpListenArgsCount = 0;
    anhttpAcceptArgsCount = 0;
    anhttpCloseArgsCount = 0;
    anhttpSocketReturn = 5;
    anhttpAcceptReturn = 6;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    server.address = "10.1.2.3";
    server.port = 54321;
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL(AnhttpErrorOK, error);

    TEST_ASSERT_EQUAL_INT(1, anhttpSocketArgsCount);
    TEST_ASSERT_EQUAL_INT(AF_INET, anhttpSocketArgs[0].domain);
    TEST_ASSERT_EQUAL_INT(SOCK_STREAM, anhttpSocketArgs[0].type);
    TEST_ASSERT_EQUAL_INT(0, anhttpSocketArgs[0].protocol);

    struct sockaddr_in expectedAddr;
    memset(&expectedAddr, 0, sizeof(expectedAddr));
    expectedAddr.sin_len = sizeof(expectedAddr);
    expectedAddr.sin_family = AF_INET;
    expectedAddr.sin_port = htons(54321);
    TEST_ASSERT_EQUAL_INT(1,
            inet_pton(AF_INET,
                "10.1.2.3",
                &expectedAddr.sin_addr));

    TEST_ASSERT_EQUAL_INT(1, anhttpBindArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpBindArgs[0].socket);
    TEST_ASSERT_EQUAL_MEMORY(&expectedAddr,
            &anhttpBindArgs[0].address,
            sizeof(expectedAddr));
    TEST_ASSERT_EQUAL(sizeof(expectedAddr), anhttpBindArgs[0].address_len);

    TEST_ASSERT_EQUAL_INT(1, anhttpListenArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpListenArgs[0].socket);
    TEST_ASSERT_EQUAL_INT(0, anhttpListenArgs[0].backlog);

    TEST_ASSERT_EQUAL_INT(1, anhttpAcceptArgsCount);
    TEST_ASSERT_EQUAL_MEMORY(&expectedAddr,
            &anhttpAcceptArgs[0].address,
            sizeof(expectedAddr));
    TEST_ASSERT_EQUAL(sizeof(expectedAddr), anhttpAcceptArgs[0].address_len);

    TEST_ASSERT_EQUAL_INT(2, anhttpCloseArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpCloseArgs[0].fd);
    TEST_ASSERT_EQUAL_INT(6, anhttpCloseArgs[1].fd);
}

static void socketFailureTest(void) {
    anhttpSocketReturn = -1;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorSystem, error);
}

static void bindFailureTest(void) {
    anhttpSocketReturn = 5;
    anhttpBindReturn = -1;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorSystem, error);
}

static void listenFailureTest(void) {
    anhttpSocketReturn = 5;
    anhttpBindReturn = 0;
    anhttpListenReturn = -1;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorSystem, error);
}

static void acceptFailureTest(void) {
    anhttpSocketReturn = 5;
    anhttpListenReturn = 0;
    anhttpAcceptReturn = -1;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorSystem, error);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(successTest);
    RUN_TEST(nonDefaultAddressTest);
    RUN_TEST(socketFailureTest);
    RUN_TEST(bindFailureTest);
    RUN_TEST(listenFailureTest);
    RUN_TEST(acceptFailureTest);
    return UNITY_END();
}
