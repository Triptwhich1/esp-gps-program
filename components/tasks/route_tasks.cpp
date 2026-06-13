#include "tasks.hpp"

namespace route_tasks {
    void append_to_route_task(void *arg) {
        route_append_task_args_t *task_args = static_cast<route_append_task_args_t*>(arg);
        route *route_arg = task_args->route_arg;
        QueueHandle_t queue_arg = task_args->queue_arg;
        TaskHandle_t rx_handle = task_args->rx_handle;

        while (1) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

            xTaskNotifyGive(rx_handle);

            gps_data_t gps_data;
            if (xQueueReceive(queue_arg, &gps_data, pdMS_TO_TICKS(2500))) {
                route_arg->append_to_route(gps_data);
                lvgl_screens::update_overview_screen(route_arg->get_num_points());
            };
        }
    }
}