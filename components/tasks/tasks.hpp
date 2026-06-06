#pragma once
#include "gps.hpp"
#include "route.hpp"
#include "task_args.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define BUFFER_SIZE 512

namespace gps_tasks
{
    void rx_task(void *arg);
}
