#pragma once
#include "gps.hpp"
#include "route.hpp"
#include "task_args.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "lvgl_screens/screens.hpp"

#define BUFFER_SIZE 512
#define GPS_RETRIEVE_MAX_ATTEMPTS 3

namespace gps_tasks
{
    void rx_task(void *arg);
}

namespace route_tasks {
    void append_to_route_task(void *arg);
}

namespace navigation_tasks {
    void navigation_task(void *arg);
}
