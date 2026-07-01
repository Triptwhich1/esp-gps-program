#include "tasks.hpp"

namespace navigation_tasks {
    void navigation_task(void *arg) {
        navigation_task_args_t *task_args = static_cast<navigation_task_args_t*>(arg);
        screen *my_screen = task_args->screen_arg;
        route *my_route = task_args->route_arg;
        QueueHandle_t queue = task_args->queue_arg;
        button_event_t button_event;

        while (1) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            xQueueReceive(queue, &button_event, portMAX_DELAY);
            ESP_LOGI("Navigation", "Button event received: %d", button_event);
            switch (button_event) {
                case BUTTON_SINGLE_CLICK: 
                    if (my_screen->get_state() == screen_state_t::INACTIVE) {
                        ESP_LOGI("Navigation", "Screen is inactive");
                        my_screen->set_state(screen_state_t::OVERVIEW, my_route);
                    } else if (my_screen->get_state() == screen_state_t::TITLE) {
                        ESP_LOGI("Navigation", "Screen is in title state");
                    //     my_screen->set_state(screen_state_t::OVERVIEW, my_route);
                    // } else if (my_screen->get_state() == screen_state_t::POPUP) {
                        // ESP_LOGI("Navigation", "Screen popup");
                        // my_screen->set_state(my_screen->next_state(), my_route);
                    } else {
                        ESP_LOGI("Navigation", "Single button press detected, cycling to next screen");
                        my_screen->set_state(my_screen->next_state(), my_route);
                    }
                    break;
                case BUTTON_LONG_PRESS_START:
                    ESP_LOGI("Navigation", "Long button press detected");
                    my_screen->set_state(screen_state_t::INACTIVE);
                    break;
                case BUTTON_DOUBLE_CLICK:
                    ESP_LOGI("Navigation", "Double button press detected");
                    break;
                default: 
                    ESP_LOGW("Navigation", "Unknown button event: %d", button_event);
                    break;
            }
        }
    }
}