#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "gps.hpp"

#define RX2 GPIO_NUM_16

gps my_gps{UART_NUM_2, RX2};

extern "C" void app_main(void)
{
    ESP_LOGI("info", "program start");

    my_gps.init();
    xTaskCreate(gps_tasks::rx_task, "rx_task", 4096, &my_gps, 1, NULL);
}
