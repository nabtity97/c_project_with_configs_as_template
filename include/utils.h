#ifndef UTILS_H
#define UITILS_H

typedef enum 
{   
    STATUS_OK                                       = 0,
    
    /* event manager module status codes */
    EVENT_MANAGER_NOT_INITIALIZED,
    EVENT_MANAGER_INVALID_HANDLER,
    EVENT_MANAGER_ALREADY_INITIALIZED,
    EVENT_MANAGER_UNSUPPORTED_EVENT,
    EVENT_MANAGER_CALLBACK_LIST_FULL, 
    EVENT_MANAGER_HANDLER_NOT_FOUND, 

} status_t;


#endif