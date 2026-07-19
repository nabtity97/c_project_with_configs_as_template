#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "event_manager.h"

void led_controller_init(void);
void led_controller_pin_accepted_event_handler(void);
void led_controller_pin_rejected_event_hander(void);


#endif