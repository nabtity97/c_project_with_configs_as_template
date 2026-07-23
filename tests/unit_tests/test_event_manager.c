#include "unity.h"
#include "event_manager.h"
#include "../../src/event_manager.c"

void setUp(void) {
    printf("Setup function\n");
}

void tearDown(void) {
    printf("Teardown function\n");
}

void test_function_should_doBlahAndBlah(void) {
    printf("first test function\n");

    TEST_ASSERT_NOT_NULL(event_manager->callbacks);
    printf("first test passed\n");

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_doBlahAndBlah);
    return UNITY_END();
}