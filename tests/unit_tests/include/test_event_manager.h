#ifndef TEST_EVENT_MANAGER_H
#define TEST_EVENT_MANAGER_H

#include "unity.h"
#include "event_manager.h"

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


#endif