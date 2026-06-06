#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "gps.hpp"

struct gps_rx_task_args_t {
    gps *gps_arg;
    QueueHandle_t queue_arg;
};