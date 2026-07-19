#include "unity.h"
#include "event_manager.h"

void setUp(void) {
    printf("Setup function\n");
}

void tearDown(void) {
    printf("Teardown function\n");
}

void test_function_should_doBlahAndBlah(void) {
    printf("first test function\n");

    TEST_ASSERT_GREATER_THAN(10, 150);
    printf("first test passed\n");

}

void test_function_should_doAlsoDoBlah(void) {
    printf("sec test function\n");

    TEST_ASSERT_GREATER_THAN(10, 100);
    printf("sec test passed\n");

}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_function_should_doAlsoDoBlah);
    return UNITY_END();
}