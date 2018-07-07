#include "unity.h"

#include "source/connection_queue.h"
#include "source/thread.h"
#include "source/list.h"

#include <string.h>
#include <assert.h>

static void basicTest(void) {
    anhttpConnectionQueue_t q;
    AnhttpError_t error = anhttpConnectionQueueInit(&q);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);

    int length;
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK,
            anhttpConnectionQueueLength(&q, &length));
    TEST_ASSERT_EQUAL_INT(0, length);

    anhttpConnection_t c1;
    memset(&c1, 0, sizeof(c1));
    c1.fd = 5;
    error = anhttpConnectionQueueAdd(&q, &c1);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK,
            anhttpConnectionQueueLength(&q, &length));
    TEST_ASSERT_EQUAL_INT(1, length);

    anhttpConnection_t c;
    error = anhttpConnectionQueueRemove(&q, &c);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);
    TEST_ASSERT_EQUAL_MEMORY(&c1, &c, sizeof(c1));
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK,
            anhttpConnectionQueueLength(&q, &length));
    TEST_ASSERT_EQUAL_INT(0, length);

    anhttpConnection_t cs[5];
    memset(cs, 0, sizeof(cs));
    for (int i = 6; i <= 10; i++) {
        cs[i-6].fd = i;
        error = anhttpConnectionQueueAdd(&q, &cs[i-6]);
        TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);
        TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK,
                anhttpConnectionQueueLength(&q, &length));
        TEST_ASSERT_EQUAL_INT(i - 5, length);
    }

    for (int i = 6; i <= 10; i++) {
        error = anhttpConnectionQueueRemove(&q, &c);
        TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);
        TEST_ASSERT_EQUAL_MEMORY(&cs[i-6], &c, sizeof(c1));
        TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK,
                anhttpConnectionQueueLength(&q, &length));
        TEST_ASSERT_EQUAL_INT(10 - i, length);
    }

    anhttpConnectionQueueFree(&q);
}

#define CONNECTIONS_MARK 0xACAC0192
#define CONNECTIONS_COUNT 10

typedef struct {
    int mark;

    anhttpConnectionQueue_t *q;
    anhttpThread_t thread;

    int desiredFds[CONNECTIONS_COUNT];
    anhttpList_t writtenFds;
    anhttpList_t readFds;
} connections_t;

static void *addConnections(void *input) {
    connections_t *cs = (connections_t *)input;
    if (cs->mark != CONNECTIONS_MARK) {
        printf("FAILURE: 0x%08X != 0x%08X\n", cs->mark, CONNECTIONS_MARK);
        assert(0);
    }

    for (int i = 0; i < CONNECTIONS_COUNT; i++) {
        anhttpConnection_t c;
        memset(&c, 0, sizeof(c));
        c.fd = cs->desiredFds[i];
        AnhttpError_t error = anhttpConnectionQueueAdd(cs->q, &c);
        if (strcmp(AnhttpErrorOK, error) == 0) {
           anhttpListAdd(&cs->writtenFds, c.fd);
        }
    }

    for (int i = 0; i < CONNECTIONS_COUNT; i++) {
        anhttpConnection_t c;
        AnhttpError_t error = anhttpConnectionQueueRemove(cs->q, &c);
        if (strcmp(AnhttpErrorOK, error) == 0) {
           anhttpListAdd(&cs->readFds, c.fd);
        }
    }

    return NULL;
}

static void initConnections(connections_t *cs,
        anhttpConnectionQueue_t *q,
        int startFd) {
    cs->mark = CONNECTIONS_MARK;

    cs->q = q;
    anhttpListInit(&cs->writtenFds, CONNECTIONS_COUNT);
    anhttpListInit(&cs->readFds, CONNECTIONS_COUNT);

    for (int i = 0; i < CONNECTIONS_COUNT; i++) {
        cs->desiredFds[i] = i + startFd;
    }
}

static void concurrentTest(void) {
    anhttpConnectionQueue_t q;
    AnhttpError_t error = anhttpConnectionQueueInit(&q);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);

    connections_t css[10];
    initConnections(&css[0], &q, 0);
    initConnections(&css[1], &q, 10);
    initConnections(&css[2], &q, 20);
    initConnections(&css[3], &q, 30);
    initConnections(&css[4], &q, 40);
    initConnections(&css[5], &q, 50);
    initConnections(&css[6], &q, 60);
    initConnections(&css[7], &q, 70);
    initConnections(&css[8], &q, 80);
    initConnections(&css[9], &q, 90);

    for (int i = 0; i < 10; i++) {
        error = anhttpThreadRun(&css[i].thread, addConnections, &css[i]);
        TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);
    }

    for (int i = 0; i < 10; i++) {
        error = anhttpThreadWait(&css[i].thread);
        TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);
    }

    int length;
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK,
            anhttpConnectionQueueLength(&q, &length));
    TEST_ASSERT_EQUAL_INT(0, length);

    int readFds[100];
    int writtenFds[100];
    memset(readFds, 0, sizeof(readFds));
    memset(writtenFds, 0, sizeof(writtenFds));
    for (int i = 0; i < 10; i++) {
        int fdReadCount = anhttpListLength(&css[i].readFds);
        for (int j = 0; j < fdReadCount; j++) {
            readFds[anhttpListGet(&css[i].readFds, j)] = 1;
        }
        int fdWrittenCount = anhttpListLength(&css[i].writtenFds);
        for (int j = 0; j < fdWrittenCount; j++) {
            writtenFds[anhttpListGet(&css[i].writtenFds, j)] = 1;
        }
    }

    int fail = 0;
    for (int i = 0; i < 100; i++) {
        if (readFds[i] == 0) {
            //printf("NOTE: fd %d was not read\n", i);
            fail = 1;
        }
        if (writtenFds[i] == 0) {
            //printf("NOTE: fd %d was not written\n", i);
            fail = 1;
        }
    }

    TEST_ASSERT_EQUAL_INT(0, fail);
}

#define SIMPLE_Q_MARK 0x1234ABCD
#define SIMPLE_Q_SPIN 0x01
#define SIMPLE_Q_DONE 0x02
#define SIMPLE_Q_READY 0x10

typedef struct {
    int mark;
    int status;
    anhttpConnectionQueue_t *q;
    anhttpConnection_t c;
} simpleQ_t;

static void *simpleRead(void *input) {
    simpleQ_t *sq = (simpleQ_t *)input;
    if (sq->mark != SIMPLE_Q_MARK) {
        printf("FAILURE: 0x%08X != 0x%08X\n", sq->mark, SIMPLE_Q_MARK);
        assert(0);
    }

    // AAA
    sq->status |= SIMPLE_Q_READY;
    // BBB
    while (sq->status & SIMPLE_Q_SPIN) {
    }
    // CCC

    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK,
            anhttpConnectionQueueRemove(sq->q, &sq->c));

    // DDD
    sq->status |= SIMPLE_Q_DONE;
    // EEE

    while (1) { }

    return NULL;
}

static void deadlockTest(void) {
    anhttpConnectionQueue_t q;
    AnhttpError_t error = anhttpConnectionQueueInit(&q);
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, error);

    simpleQ_t readSq = {
        .mark = SIMPLE_Q_MARK,
        .status = SIMPLE_Q_SPIN,
        .q = &q,
    };
    anhttpThread_t readThread;
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK,
            anhttpThreadRun(&readThread, simpleRead, &readSq));

    // AAA
    while (!(readSq.status & SIMPLE_Q_READY)) {
    }
    // BBB
    readSq.status &= ~ SIMPLE_Q_SPIN;
    // CCC

    // This is race'y, but it will have to do.

    anhttpConnection_t c = {
        .fd = 5,
    };
    TEST_ASSERT_EQUAL_STRING(AnhttpErrorOK, anhttpConnectionQueueAdd(&q, &c));

    // DDD
    while (!(readSq.status & SIMPLE_Q_DONE)) {
    }
    // EEE

    int length = -1;
    TEST_ASSERT_EQUAL_INT(AnhttpErrorOK,
            anhttpConnectionQueueLength(&q, &length));
    TEST_ASSERT_EQUAL_INT(0, length);
    TEST_ASSERT_EQUAL_INT(5, readSq.c.fd);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(basicTest);
    RUN_TEST(concurrentTest);
    RUN_TEST(deadlockTest);
    return UNITY_END();
}
