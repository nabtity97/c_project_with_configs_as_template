#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include <stdint.h>

#define MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT (10U)

typedef enum
{
    /* Keypad Events */
    EVENT_PIN_ACCEPTED = 0,
    EVENT_PIN_REJECTED,

    /* Motor Events */
    EVENT_LOCK_STARTED,
    EVENT_LOCK_COMPLETED,
    EVENT_UNLOCK_STARTED,
    EVENT_UNLOCK_COMPLETED,
    EVENT_MOTOR_ERROR,

    /* Battery Events */
    EVENT_BATTERY_LOW,

    EVENT_MAXIMUM

} event_type_e;

typedef struct 
{
    bool is_empty;
    void (*registered_callback)(void);
} callbacks_handler_t;

typedef struct 
{
    event_type_e event_type;
    callbacks_handler_t callbacks[MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT];
} event_manager_t;

status_t event_manager_init(void);
status_t event_manager_deinit(void);

status_t event_manager_register(event_type_e event_type, void (*handler) (void));
status_t event_manager_unregister(event_type_e event_type, void (*handler) (void));
status_t event_manager_publish(event_type_e event_type);

#endif