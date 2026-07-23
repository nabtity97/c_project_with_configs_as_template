#include "../include/event_manager.h"

static event_manager_t event_manager[EVENT_MAXIMUM] = { 0 };

void event_manager_init(void)
{   
    printf("[Info] event manger init \n");

    for(uint8_t i = 0; i < EVENT_MAXIMUM; i++)
    {
        event_manager[i].event_type = i; // set the event type

        for (uint8_t j = 0U; j < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; j++)
        {
            event_manager[i].callbacks[j].is_empty = true; 
            event_manager[i].callbacks[j].registered_callback = NULL;
        }
    }
}

void event_manager_register(event_type_e event_type, void (*handler) (void))
{
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
                }
            }
        }
    }
}

void event_manager_unregister(event_type_e event_type, void (*handler) (void))
{
    for(int i = 0; i < EVENT_MAXIMUM; i++)
    {
        if(event_type == event_manager[i].event_type)
        {
            for(int j = 0; j < MAX_NUM_OF_CALLBACKS_FOR_EACH_EVENT; j++)
            {
                if(event_manager[i].callbacks[j].registered_callback == handler)
                {    
                    event_manager[i].callbacks[j].is_empty = true;
                }
            }
        }
    }
}

void event_manager_publish(event_type_e event_type)
{
    (void) event_type;
}