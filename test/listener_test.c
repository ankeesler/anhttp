#include "unity.h"

#include "anhttp/anhttp.h"

#include "source/syscall_stubs.h"
#include "source/listener.h"
#include "source/util.h"

static void createSuccessTest(void) {
    SYSCALL_STUBS_H_RESET();
    anhttpSocketReturn = 5;
    anhttpAcceptReturn = 6;

    int listener = anhttpCreateListener("192.168.1.2", 4444);
    TEST_ASSERT_NOT_EQUAL(-1, listener);
    TEST_ASSERT_NOT_EQUAL(0, listener);

    TEST_ASSERT_EQUAL_INT(1, anhttpSocketArgsCount);
    TEST_ASSERT_EQUAL_INT(AF_INET, anhttpSocketArgs[0].domain);
    TEST_ASSERT_EQUAL_INT(SOCK_STREAM, anhttpSocketArgs[0].type);
    TEST_ASSERT_EQUAL_INT(0, anhttpSocketArgs[0].protocol);

    struct sockaddr_in expectedAddr;
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK,
            anhttpMakeSocketAddress("192.168.1.2",
                4444,
                &expectedAddr));

    TEST_ASSERT_EQUAL_INT(1, anhttpBindArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpBindArgs[0].socket);
    TEST_ASSERT_EQUAL_MEMORY(&expectedAddr,
            &anhttpBindArgs[0].address,
            sizeof(expectedAddr));
    TEST_ASSERT_EQUAL(sizeof(expectedAddr), anhttpBindArgs[0].address_len);

    TEST_ASSERT_EQUAL_INT(1, anhttpListenArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpListenArgs[0].socket);
    TEST_ASSERT_EQUAL_INT(0, anhttpListenArgs[0].backlog);

    TEST_ASSERT_EQUAL_INT(0, anhttpCloseArgsCount);
}

static void createSocketFailureTest(void) {
    SYSCALL_STUBS_H_RESET();
    anhttpSocketReturn = -1;

    int listener = anhttpCreateListener("192.168.1.2", 4444);
    TEST_ASSERT_EQUAL_INT(-1, listener);
}

static void createBindFailureTest(void) {
    SYSCALL_STUBS_H_RESET();
    anhttpSocketReturn = 5;
    anhttpBindReturn = -1;

    int listener = anhttpCreateListener("192.168.1.2", 4444);
    TEST_ASSERT_EQUAL_INT(-1, listener);

    TEST_ASSERT_EQUAL_INT(1, anhttpCloseArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpCloseArgs[0].fd);
}

static void createListenFailureTest(void) {
    SYSCALL_STUBS_H_RESET();
    anhttpSocketReturn = 5;
    anhttpListenReturn = -1;

    int listener = anhttpCreateListener("192.168.1.2", 4444);
    TEST_ASSERT_EQUAL_INT(-1, listener);

    TEST_ASSERT_EQUAL_INT(1, anhttpCloseArgsCount);
    TEST_ASSERT_EQUAL_INT(5, anhttpCloseArgs[0].fd);
}

static void startSuccessTest(void) {
    //anhttpThread_t thread;
    //anhttpConnectionQueue_t connectionQ;
    //AnhttpError_t error = anhttpStartListener(5, &thread, &connectionQ);
    //TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();

    RUN_TEST(createSuccessTest);
    RUN_TEST(createSocketFailureTest);
    RUN_TEST(createBindFailureTest);
    RUN_TEST(createListenFailureTest);

    RUN_TEST(startSuccessTest);

    return UNITY_END();
}
