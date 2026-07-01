#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "gps.hpp"
#include "route.hpp"
#include "screen.hpp"
#include "iot_button.h"

struct gps_rx_task_args_t {
    gps *gps_arg;
    QueueHandle_t queue_arg;
};

struct route_append_task_args_t {
    route *route_arg;
    screen *screen_arg;
    QueueHandle_t queue_arg;
    TaskHandle_t rx_handle;
};

struct navigation_task_args_t {
    screen *screen_arg;
    route *route_arg;
    QueueHandle_t queue_arg;
};

struct btn_cb_args_t {
    TaskHandle_t task_handle;
    button_event_t button_event;
    QueueHandle_t queue_arg;
};