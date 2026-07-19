#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include <stdio.h>
#include <stdint.h>
#include "utils.h"
#include <stdbool.h>

#define DEVICE_ID        (0xF9F9F9F9U)


typedef struct 
{
    uint32_t device_id;
    uint32_t boot_counter;
    float    temp;
    uint8_t  humidity;
    uint16_t pressure;
    uint16_t battery_voltage;

} device_info_t;



void device_info_init(void);

/* Device ID */
void     device_info_set_device_id(uint32_t device_id);
uint32_t device_info_get_device_id(void);

/* Boot Counter */
void     device_info_set_boot_counter(uint32_t boot_counter);
uint32_t device_info_get_boot_counter(void);

/* Temperature */
void  device_info_set_temp(float temp);
float device_info_get_temp(void);

/* Humidity */
void    device_info_set_humidity(uint8_t humidity);
uint8_t device_info_get_humidity(void);

/* Pressure */
void     device_info_set_pressure(uint16_t pressure);
uint16_t device_info_get_pressure(void);

/* Battery Voltage */
void     device_info_set_battery_voltage(uint16_t battery_voltage);
uint16_t device_info_get_battery_voltage(void);


#endif