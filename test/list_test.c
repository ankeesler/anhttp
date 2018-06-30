#include "source/list.h"

#include "unity.h"

static void basicIntListTest(void) {
    anhttpList_t myList;
    anhttpListInit(&myList, 5);
    TEST_ASSERT_EQUAL_INT(0, anhttpListLength(&myList));

    anhttpListAdd(&myList, 1);
    TEST_ASSERT_EQUAL_INT(1, anhttpListGet(&myList, 0));
    TEST_ASSERT_EQUAL_INT(1, anhttpListLength(&myList));

    anhttpListAdd(&myList, 2);
    TEST_ASSERT_EQUAL_INT(1, anhttpListGet(&myList, 0));
    TEST_ASSERT_EQUAL_INT(2, anhttpListGet(&myList, 1));
    TEST_ASSERT_EQUAL_INT(2, anhttpListLength(&myList));

    anhttpListAdd(&myList, 3);
    anhttpListAdd(&myList, 4);
    anhttpListAdd(&myList, 5);
    anhttpListAdd(&myList, 6);
    TEST_ASSERT_EQUAL_INT(1, anhttpListGet(&myList, 0));
    TEST_ASSERT_EQUAL_INT(2, anhttpListGet(&myList, 1));
    TEST_ASSERT_EQUAL_INT(3, anhttpListGet(&myList, 2));
    TEST_ASSERT_EQUAL_INT(4, anhttpListGet(&myList, 3));
    TEST_ASSERT_EQUAL_INT(5, anhttpListGet(&myList, 4));
    TEST_ASSERT_EQUAL_INT(6, anhttpListGet(&myList, 5));
    TEST_ASSERT_EQUAL_INT(6, anhttpListLength(&myList));

    anhttpListFree(&myList);
}

typedef struct {
    int a;
    const char *b;
} MyType_t;

static void structListTest(void) {
    anhttpList_t myList;
    anhttpListInit(&myList, 5);
    TEST_ASSERT_EQUAL_INT(0, anhttpListLength(&myList));

    MyType_t myThing1 = {
        .a = 1,
        .b = "my thing 1",
    };
    anhttpListAdd(&myList, &myThing1);
    MyType_t *myThing1Ptr = (MyType_t *)anhttpListGet(&myList, 0);
    TEST_ASSERT_EQUAL_INT(1, myThing1Ptr->a);
    TEST_ASSERT_EQUAL_STRING("my thing 1", myThing1Ptr->b);
    TEST_ASSERT_EQUAL_INT(1, anhttpListLength(&myList));

    MyType_t myThings[5] = {
        {
            .a = 2,
            .b = "my thing 2",
        },
        {
            .a = 3,
            .b = "my thing 3",
        },
        {
            .a = 4,
            .b = "my thing 4",
        },
        {
            .a = 5,
            .b = "my thing 5",
        },
        {
            .a = 6,
            .b = "my thing 6",
        },
    };
    for (int i = 0; i < 5; i++) {
        anhttpListAdd(&myList, myThings + i);
        MyType_t *myThingPtr = (MyType_t *)anhttpListGet(&myList, i + 1);
        TEST_ASSERT_EQUAL_INT(i + 2, myThingPtr->a);

        char string[11];
        sprintf(string, "my thing %d", i + 2);
        TEST_ASSERT_EQUAL_STRING(string, myThingPtr->b);
    }

    anhttpListFree(&myList);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(basicIntListTest);
    RUN_TEST(structListTest);
    return UNITY_END();
}
