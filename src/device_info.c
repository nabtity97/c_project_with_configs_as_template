#include "../include/device_info.h"

static device_info_t device_info;
static bool is_initilaized = false;

void device_info_init(void)
{
    device_info.battery_voltage = 0;
    device_info.boot_counter    = 0;
    device_info.device_id      = DEVICE_ID;
    device_info.humidity       = 0;
    device_info.pressure       = 0;
    device_info.temp           = 0.0f;
}


void device_info_set_device_id(uint32_t device_id)
{
    if(!is_initilaized)
        return;
    device_info.device_id = device_id;
}

uint32_t device_info_get_device_id(void)
{
    return device_info.device_id;
}

void device_info_set_temp(float temp)
{
    device_info.temp = temp;
}

float device_info_get_temp(void)
{
    return device_info.temp;
}

void device_info_set_humidity(uint8_t humidity)
{
    device_info.humidity = humidity;
}

uint8_t device_info_get_humidity(void)
{
    return device_info.humidity;
}

void device_info_set_pressure(uint16_t pressure)
{
    device_info.pressure = pressure;
}

uint16_t device_info_get_pressure(void)
{
    return device_info.pressure;
}

void device_info_set_battery_voltage(uint16_t battery_voltage)
{
    device_info.battery_voltage = battery_voltage;
}

uint16_t device_info_get_battery_voltage(void)
{
    return device_info.battery_voltage;
}