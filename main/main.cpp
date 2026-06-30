#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "gps.hpp"
#include "task_args.cpp"
#include "tasks.hpp"
#include "timer.hpp"
#include "esp_pm.h"
#include "screen.hpp"
#include "lvgl_screens/screens.hpp"
#include "navigation.hpp"

#include "iot_button.h"
#include "button_gpio.h"


#define RX2 GPIO_NUM_16
#define BTN_PIN GPIO_NUM_12

QueueHandle_t route_Queue;
QueueHandle_t navigation_Queue;
gps my_gps{UART_NUM_2, RX2};
route my_route{};
screen my_screen{GPIO_NUM_22, GPIO_NUM_21, 128, 64};
timer append_timer{15};
button_handle_t btn;

static TaskHandle_t append_to_route_task_handle = NULL;
static TaskHandle_t gps_rx_task_handle = NULL;
static TaskHandle_t navigation_task_handle = NULL;

void append_to_route_timer_cb (TimerHandle_t xTimer) {
    if (append_to_route_task_handle != NULL) {
        xTaskNotifyGive(append_to_route_task_handle);
    }
}

void pm_init() {
    esp_pm_config_t pm_config {
        .max_freq_mhz = 160,
        .min_freq_mhz = 40,
        .light_sleep_enable = true
    };

    esp_pm_configure(&pm_config);
}

void btn_init() {

    button_config_t cfg = {
        .long_press_time = 1500,
        .short_press_time = 100
    };

    button_gpio_config_t gpio_cfg = {
        .gpio_num = BTN_PIN,
        .active_level = 0
    };

    iot_button_new_gpio_device(&cfg, &gpio_cfg, &btn);
    iot_button_register_cb(btn, BUTTON_SINGLE_CLICK, NULL, navigation::short_press_cb, navigation_task_handle);
}

extern "C" void app_main(void)
{
    ESP_LOGI("info", "program start");

    // pm_init();

    route_Queue = xQueueCreate(10, sizeof(gps_data_t));

    static gps_rx_task_args_t rx_task_args{
        .gps_arg = &my_gps,
        .queue_arg = route_Queue
    };

    my_screen.init();
    my_gps.init();
    xTaskCreate(gps_tasks::rx_task, "rx_task", 4096, &rx_task_args, 1, &gps_rx_task_handle);

    static route_append_task_args_t append_task_args {
        .route_arg = &my_route,
        .screen_arg = &my_screen,
        .queue_arg = route_Queue,
        .rx_handle = gps_rx_task_handle
    };

    static navigation_task_args_t navigation_task_args {
        .screen_arg = &my_screen
    };

    xTaskCreate(route_tasks::append_to_route_task, "append_task", 4096, &append_task_args, 1, &append_to_route_task_handle);

    TimerHandle_t append_timer_handle = xTimerCreate("append_timer", pdMS_TO_TICKS(append_timer.get_interval() * 1000), pdTRUE, NULL, append_to_route_timer_cb);
    xTimerStart(append_timer_handle, 0);

    xTaskCreate(navigation_tasks::navigation_task, "navigation_task", 2048, &navigation_task_args, 1, &navigation_task_handle);

    btn_init();

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
