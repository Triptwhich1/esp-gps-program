#include "tasks.hpp"

namespace navigation_tasks {
    void navigation_task(void *arg) {
        navigation_task_args_t *task_args = static_cast<navigation_task_args_t*>(arg);
        screen *my_screen = task_args->screen_arg;
        route *my_route = task_args->route_arg;
        while (1) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            ESP_LOGI("Navigation", "Button pressed, starting navigation task");
            my_screen->set_state(my_screen->next_state(), my_route);
        }
    }
}