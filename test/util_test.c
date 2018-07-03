#include "unity.h"

#include "anhttp/anhttp.h"

#include "source/util.h"

#include <arpa/inet.h>
#include <netinet/in.h>

static void makeSocketAddressTest(void) {
    struct sockaddr_in sockAddr;
    AnhttpError_t error = anhttpMakeSocketAddress("127.0.0.1",
            12345,
            &sockAddr);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);
    TEST_ASSERT_EQUAL_INT(sizeof(sockAddr), sockAddr.sin_len);
    TEST_ASSERT_EQUAL_INT(AF_INET, sockAddr.sin_family);
    TEST_ASSERT_EQUAL_INT(htons(12345), sockAddr.sin_port);
    TEST_ASSERT_EQUAL_INT(1,
            (sockAddr.sin_addr.s_addr & 0xFF000000) >> 24);
    TEST_ASSERT_EQUAL_INT(0,
            (sockAddr.sin_addr.s_addr & 0x00FF0000) >> 16);
    TEST_ASSERT_EQUAL_INT(0,
            (sockAddr.sin_addr.s_addr & 0x00FF0000) >> 8);
    TEST_ASSERT_EQUAL_INT(127, sockAddr.sin_addr.s_addr & 0x000000FF);

    TEST_ASSERT_EQUAL_STRING("127.0.0.1", inet_ntoa(sockAddr.sin_addr));
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(makeSocketAddressTest);
    return UNITY_END();
}
