#pragma once
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

class timer
{
private:
    uint8_t _interval;
    TimerHandle_t _timer_handle;
public:
    timer(uint8_t interval);
    ~timer();
    void set_interval(uint8_t interval);
    uint8_t get_interval();
};
