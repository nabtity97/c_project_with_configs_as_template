#include "../include/event_manager.h"

static event_manager_t event_manager[EVENT_MAXIMUM] = { 0 };
static bool is_event_manager_initilaized = false;

status_t event_manager_init(void)
{   
    if(is_event_manager_initilaized)
        return EVENT_MANAGER_ALREADY_INITIALIZED;

    for(uint8_t i = 0; i < EVENT_MAXIMUM; i++)
    {
        event_manager[i].event_type = i;

        for (uint8_t j = 0U; j < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; j++)
        {
            event_manager[i].callbacks[j].is_empty = true; 
            event_manager[i].callbacks[j].registered_callback = NULL;
        }
    }

    is_event_manager_initilaized = true;
    
    return STATUS_OK;
}

status_t event_manager_deinit(void)
{   
    if(!is_event_manager_initilaized)
        return EVENT_MANAGER_NOT_INITIALIZED;

    for(uint8_t i = 0; i < EVENT_MAXIMUM; i++)
    {
        event_manager[i].event_type = EVENT_MAXIMUM;

        for (uint8_t j = 0U; j < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; j++)
        {
            event_manager[i].callbacks[j].is_empty = true; 
            event_manager[i].callbacks[j].registered_callback = NULL;
        }
    }

    is_event_manager_initilaized = false;
    
    return STATUS_OK;
}

status_t event_manager_register(event_type_e event_type, void (*handler) (void))
{   
    // check if the module has been initialized.
    if(!is_event_manager_initilaized)
        return EVENT_MANAGER_NOT_INITIALIZED;
    
    if(NULL == handler)
        return EVENT_MANAGER_INVALID_HANDLER;

    // Check if the event is valid event. 
    if(event_type < EVENT_PIN_ACCEPTED || event_type >= EVENT_MAXIMUM)
        return  EVENT_MANAGER_UNSUPPORTED_EVENT;

    /* Search for the first available callback slot for the requested event. */
    for(uint8_t i = 0; i < EVENT_MAXIMUM; i++)
    {
        if(event_type == event_manager[i].event_type)
        {
            for(uint8_t j = 0; j < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; j++)
            {
                if(event_manager[i].callbacks[j].is_empty)
                {    
                    event_manager[i].callbacks[j].is_empty = false;
                    event_manager[i].callbacks[j].registered_callback = handler;
                    
                    return STATUS_OK;                    
                }
            }
        }
    }

    /* No free callback slot was found for this event. */
    return EVENT_MANAGER_CALLBACK_LIST_FULL;
}

status_t event_manager_unregister(event_type_e event_type, void (*handler) (void))
{   
    // check if the module has been initialized.
    if(!is_event_manager_initilaized)
        return EVENT_MANAGER_NOT_INITIALIZED;
    
    if(NULL == handler)
        return EVENT_MANAGER_INVALID_HANDLER;

    // Check if the event is valid event. 
    if(event_type < EVENT_PIN_ACCEPTED || event_type >= EVENT_MAXIMUM)
        return  EVENT_MANAGER_UNSUPPORTED_EVENT;

    for(uint8_t i = 0; i < EVENT_MAXIMUM; i++)
    {
        if(event_type == event_manager[i].event_type)
        {
            for(uint8_t j = 0; j < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; j++)
            {
                if(event_manager[i].callbacks[j].registered_callback == handler)
                {    
                    event_manager[i].callbacks[j].is_empty = true;
                    return STATUS_OK;
                }
            }
        }
    }

    /* Could not find an handler in this event callbacks list. */
    return EVENT_MANAGER_HANDLER_NOT_FOUND;
}

status_t event_manager_publish(event_type_e event_type)
{
    // check if the module has been initialized.
    if(!is_event_manager_initilaized)
        return EVENT_MANAGER_NOT_INITIALIZED;
    
    // Check if the event is valid event. 
    if(event_type < EVENT_PIN_ACCEPTED || event_type >= EVENT_MAXIMUM)
        return EVENT_MANAGER_UNSUPPORTED_EVENT;

    for(uint8_t i = 0; i < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; i++)
    {
        if(!event_manager[event_type].callbacks[i].is_empty)
        {
            event_manager[event_type].callbacks[i].registered_callback();
        }
    }

    return STATUS_OK;
}