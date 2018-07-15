#include "anhttp/anhttp.h"

#include "unity.h"

#include "source/util.h"

#include "source/syscall_stubs.h"
#include "source/listener_stubs.h"
#include "source/connection_queue_stubs.h"
#include "source/thread_stubs.h"
#include "source/http_stubs.h"

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

static ssize_t readStub(int fd, void *buf, size_t buf_size) {
    static int calls = 0;
    ++calls;
    TEST_ASSERT_TRUE(calls <= 3);
    buf = "hello";
    return 5;
}

static AnhttpError_t parseHttpRequestStub(AnhttpRequest_t *req,
        void *buf,
        size_t bufLen) {
    req->method = ANHTTP_METHOD_GET;
    req->uri = "/tuna/fish";
    req->payload = (unsigned char *)"hello";
    req->payloadLen = 5;
    return AnhttpErrorOK;
}

static int fakeHandlerCalled = 0;
static void fakeHandler(AnhttpResponse_t *rsp, const AnhttpRequest_t *req) {
    fakeHandlerCalled = 1;

    TEST_ASSERT_EQUAL_INT(ANHTTP_STATUS_OK, rsp->status);

    TEST_ASSERT_EQUAL_STRING(ANHTTP_METHOD_GET, req->method);
    TEST_ASSERT_EQUAL_STRING("/tuna/fish", req->uri);

    char *payload = "hello";
    TEST_ASSERT_EQUAL_INT(5, req->payloadLen);
    TEST_ASSERT_EQUAL_MEMORY(payload, req->payload, 5);

    rsp->payload = (unsigned char *)"hello";
    rsp->payloadLen = 5;
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
    anhttpReadFunction = readStub;
    anhttpParseHttpRequestFunction = parseHttpRequestStub;

    AnhttpServer_t server;
    memset(&server, 0, sizeof(server));
    server.handler = fakeHandler;
    AnhttpError_t error = AnhttpListenAndServe(&server);
    TEST_ASSERT_EQUAL(AnhttpErrorOK, error);

    TEST_ASSERT_EQUAL_INT(3, anhttpReadArgsCount);
    TEST_ASSERT_EQUAL_INT(6, anhttpReadArgs[0].fd);
    TEST_ASSERT_EQUAL_INT(7, anhttpReadArgs[1].fd);
    TEST_ASSERT_EQUAL_INT(8, anhttpReadArgs[2].fd);

    TEST_ASSERT_EQUAL_INT(3, anhttpParseHttpRequestArgsCount);

    const char *response = "hello";
    TEST_ASSERT_EQUAL_INT(3, anhttpWriteArgsCount);
    TEST_ASSERT_EQUAL_INT(6, anhttpWriteArgs[0].fd);
    TEST_ASSERT_EQUAL_MEMORY(response, anhttpWriteArgs[0].buffer, 5);
    TEST_ASSERT_EQUAL_INT(7, anhttpWriteArgs[1].fd);
    TEST_ASSERT_EQUAL_MEMORY(response, anhttpWriteArgs[1].buffer, 5);
    TEST_ASSERT_EQUAL_INT(8, anhttpWriteArgs[2].fd);
    TEST_ASSERT_EQUAL_MEMORY(response, anhttpWriteArgs[2].buffer, 5);

    TEST_ASSERT_EQUAL_INT(1, fakeHandlerCalled);

    TEST_ASSERT_EQUAL_INT(3, anhttpCloseArgsCount);
    TEST_ASSERT_EQUAL_INT(6, anhttpCloseArgs[0].fd);
    TEST_ASSERT_EQUAL_INT(7, anhttpCloseArgs[1].fd);
    TEST_ASSERT_EQUAL_INT(8, anhttpCloseArgs[2].fd);

    TEST_ASSERT_EQUAL_INT(1, anhttpThreadCancelArgsCount);
}

static void readFailServingTest(void) {
}

static void parseFailServingTest(void) {
}

static void writeFailServingTest(void) {
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
    RUN_TEST(readFailServingTest);
    RUN_TEST(parseFailServingTest);
    RUN_TEST(writeFailServingTest);

    return UNITY_END();
}
