#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "gps.hpp"
#include "task_args.cpp"
#include "tasks.hpp"

#define RX2 GPIO_NUM_16
#define BTN_PIN GPIO_NUM_12

QueueHandle_t route_Queue;
gps my_gps{UART_NUM_2, RX2};
route my_route{};

extern "C" void app_main(void)
{
    ESP_LOGI("info", "program start");
    route_Queue = xQueueCreate(10, sizeof(gps_data_t));

    static gps_rx_task_args_t rx_task_args{
        .gps_arg = &my_gps,
        .queue_arg = route_Queue
    };

    static route_append_task_args_t append_task_args {
        .route_arg = &my_route,
        .queue_arg = route_Queue
    };

    my_gps.init();
    xTaskCreate(gps_tasks::rx_task, "rx_task", 4096, &rx_task_args, 1, NULL);
    xTaskCreate(route_tasks::append_to_route_task, "append_task", 4096, &append_task_args, 1, NULL);
}
