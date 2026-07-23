#include "unity.h"
#include "event_manager.h"
#include "../../src/event_manager.c"

void setUp(void)
{
    printf("[INFO] Setup function\n");
}

void tearDown(void)
{
    printf("[INFO] Teardown function\n");
}

void test_event_manger_init(void)
{
    // call the function under test.
    event_manager_init();

    // validate the event_manager has been updated correctly after init.
    for (uint8_t i = EVENT_PIN_ACCEPTED; i < EVENT_MAXIMUM; i++)
    {
        TEST_ASSERT_EQUAL(event_manager[i].event_type, i);

        for (uint8_t j = 0U; j < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; j++)
        {
            TEST_ASSERT_EQUAL(
                event_manager[i].callbacks[j].is_empty,
                true);
            
            TEST_ASSERT_NULL(event_manager[i].callbacks[j].registered_callback);
        }
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_event_manger_init);
    return UNITY_END();
}