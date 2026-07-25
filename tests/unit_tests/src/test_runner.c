#include "unity.h"
#include "test_event_manager.h"

int main(void)
{
    UNITY_BEGIN();

    /* Event Manager tests */
    RUN_TEST(test_event_manger_init_pass);
    RUN_TEST(test_event_manger_register_pass);
    RUN_TEST(test_event_manager_init_fail_already_initialized);
    RUN_TEST(test_event_manger_register_fail_callback_list_full);
    RUN_TEST(test_event_manger_register_fail_unsupported_event);
    RUN_TEST(test_event_manger_register_fail_invalid_handler);
    RUN_TEST(test_event_manger_register_fail_module_uninitialized);

    return UNITY_END();
}