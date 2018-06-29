#include "anhttp/anhttp.h"

#include "unity.h"

#include <assert.h>

static void a(void) {
}

static void b(void) {
}

static void c(void) {
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();
    RUN_TEST(a);
    RUN_TEST(b);
    RUN_TEST(c);
    return UNITY_END();
}
