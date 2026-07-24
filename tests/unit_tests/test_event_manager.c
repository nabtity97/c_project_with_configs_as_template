#include "unity.h"
#include "event_manager.h"
#include "../../src/event_manager.c"

void setUp(void);
void tearDown(void);

/* Test Functions */
void test_event_manger_init_pass(void);
void test_event_manger_register_pass(void);
void test_event_manager_init_fail_already_initialized(void);
void test_event_manger_register_fail_module_uninitialized(void);
void test_event_manger_register_fail_invalid_handler(void);
void test_event_manger_register_fail_unsupported_event(void);
void test_event_manger_register_fail_callback_list_full(void);

/* Callback invocation counters */
static uint32_t helper0_calls  = 0;
static uint32_t helper1_calls  = 0;
static uint32_t helper2_calls  = 0;
static uint32_t helper3_calls  = 0;
static uint32_t helper4_calls  = 0;
static uint32_t helper5_calls  = 0;
static uint32_t helper6_calls  = 0;
static uint32_t helper7_calls  = 0;
static uint32_t helper8_calls  = 0;
static uint32_t helper9_calls  = 0;
static uint32_t helper10_calls = 0;

/* Dummy callback functions */
static void helper_function0(void)  { helper0_calls++; }
static void helper_function1(void)  { helper1_calls++; }
static void helper_function2(void)  { helper2_calls++; }
static void helper_function3(void)  { helper3_calls++; }
static void helper_function4(void)  { helper4_calls++; }
static void helper_function5(void)  { helper5_calls++; }
static void helper_function6(void)  { helper6_calls++; }
static void helper_function7(void)  { helper7_calls++; }
static void helper_function8(void)  { helper8_calls++; }
static void helper_function9(void)  { helper9_calls++; }
static void helper_function10(void) { helper10_calls++; }

/* Helper function to reset all counters before each test */
static void reset_helper_call_counters(void);

/* Array holds all the helper functions */
static void (*helper_functions[])(void) =
{
    helper_function0,
    helper_function1,
    helper_function2,
    helper_function3,
    helper_function4,
    helper_function5,
    helper_function6,
    helper_function7,
    helper_function8,
    helper_function9,
    helper_function10
};

/* main function */
int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_event_manger_init_pass);
    RUN_TEST(test_event_manger_register_pass);
    RUN_TEST(test_event_manager_init_fail_already_initialized);
    RUN_TEST(test_event_manger_register_fail_callback_list_full);
    RUN_TEST(test_event_manger_register_fail_unsupported_event);
    RUN_TEST(test_event_manger_register_fail_invalid_handler);
    RUN_TEST(test_event_manger_register_fail_module_uninitialized);

    // TODO: ADD TESTS FOR unregister and puplish functions. 


    return UNITY_END();
}

void setUp(void)
{
    // to setup the event manager module.
    TEST_ASSERT_EQUAL(STATUS_OK, event_manager_init());
}

void tearDown(void)
{   
    // to clean up the moduel.
    event_manager_deinit();
    reset_helper_call_counters();
}

void test_event_manger_init_pass(void)
{
    // validate the event_manager has been updated correctly after init.
    for (uint8_t i = EVENT_PIN_ACCEPTED; i < EVENT_MAXIMUM; i++)
    {
        TEST_ASSERT_EQUAL(i, event_manager[i].event_type);

        for (uint8_t j = 0U; j < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; j++)
        {
            TEST_ASSERT_TRUE(event_manager[i].callbacks[j].is_empty);
            TEST_ASSERT_NULL(event_manager[i].callbacks[j].registered_callback);
        }
    }

    TEST_ASSERT_TRUE(is_event_manager_initilaized);
}

void test_event_manager_init_fail_already_initialized(void)
{
    TEST_ASSERT_EQUAL(EVENT_MANAGER_ALREADY_INITIALIZED,
                      event_manager_init());
}

void test_event_manger_register_pass(void)
{   
    /* Register the maximum number of callbacks for every event. */
    for(uint8_t i = 0; i < EVENT_MAXIMUM; i++)
    {
        // register 10 callsback for one event -> expect ok
        for(uint8_t j = 0; j < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; j++)
        {
            TEST_ASSERT_EQUAL(STATUS_OK,
                 event_manager_register(i, helper_functions[j]));
        }
    }

    /* Verify that every callback was stored in the expected slot. */
    for(uint8_t i = 0; i < EVENT_MAXIMUM; i++)
    {
        // register 10 callsback for one event -> expect ok
        for(uint8_t j = 0; j < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; j++)
        {   
            TEST_ASSERT_FALSE(event_manager[i].callbacks[j].is_empty);
            TEST_ASSERT_EQUAL_PTR(helper_functions[j], event_manager[i].callbacks[j].registered_callback);
        }
    }
}

void test_event_manger_register_fail_module_uninitialized(void)
{
    TEST_ASSERT_EQUAL(STATUS_OK,
         event_manager_deinit());
    TEST_ASSERT_EQUAL(EVENT_MANAGER_NOT_INITIALIZED,
         event_manager_register(EVENT_PIN_ACCEPTED, helper_functions[0]));
}

void test_event_manger_register_fail_invalid_handler(void)
{
    TEST_ASSERT_EQUAL(EVENT_MANAGER_INVALID_HANDLER,
         event_manager_register(EVENT_PIN_ACCEPTED, NULL));
}

void test_event_manger_register_fail_unsupported_event(void)
{   
    const event_type_e invalid_event_below_range = (event_type_e)-1;
    const event_type_e invalid_event_above_range = (event_type_e)EVENT_MAXIMUM;

    TEST_ASSERT_EQUAL(EVENT_MANAGER_UNSUPPORTED_EVENT,
         event_manager_register(invalid_event_below_range, helper_functions[0]));
    TEST_ASSERT_EQUAL(EVENT_MANAGER_UNSUPPORTED_EVENT,
         event_manager_register(invalid_event_above_range, helper_functions[0]));
}

void test_event_manger_register_fail_callback_list_full(void)
{
    /* Register the maximum number of callbacks for EVENT_PIN_ACCEPTED event. */
    for(uint8_t i = 0; i < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; i++)
    {
        TEST_ASSERT_EQUAL(STATUS_OK,
             event_manager_register(EVENT_PIN_ACCEPTED, helper_functions[i]));
    }

    /* Add one more callback. List full error code is expected to be returned. */
    TEST_ASSERT_EQUAL(EVENT_MANAGER_CALLBACK_LIST_FULL,
         event_manager_register(EVENT_PIN_ACCEPTED, helper_functions[MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT]));

    /* A full callback list for one event must not affect other events. */
    TEST_ASSERT_EQUAL(STATUS_OK,
         event_manager_register(EVENT_PIN_REJECTED, helper_functions[0]));
}

/* HELPER FUNCTIONS --------------------- */

static void reset_helper_call_counters(void)
{
    helper0_calls  = 0;
    helper1_calls  = 0;
    helper2_calls  = 0;
    helper3_calls  = 0;
    helper4_calls  = 0;
    helper5_calls  = 0;
    helper6_calls  = 0;
    helper7_calls  = 0;
    helper8_calls  = 0;
    helper9_calls  = 0;
    helper10_calls = 0;
}
