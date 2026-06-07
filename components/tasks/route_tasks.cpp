#include "tasks.hpp"

namespace route_tasks {
    void append_to_route_task(void *arg) {
        while (1) {
            route_append_task_args_t *task_args = static_cast<route_append_task_args_t*>(arg);
            route *route_arg = task_args->route_arg;
            QueueHandle_t queue_arg = task_args->queue_arg;

            gps_data_t gps_data;
            xQueueReceive(queue_arg, &gps_data, pdMS_TO_TICKS(10));

            route_arg->append_to_route(gps_data);
        }
    }
}