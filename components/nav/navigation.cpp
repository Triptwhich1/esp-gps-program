#include "navigation.hpp"

namespace navigation {
    void button_press_cb(void *button_handle, void *usr_data) {
        btn_cb_args_t *btn_args = static_cast<btn_cb_args_t*>(usr_data);
        QueueHandle_t queue = btn_args->queue_arg;
        button_event_t button_event = btn_args->button_event;
        xQueueSend(queue, &button_event, 0);
        xTaskNotifyGive(btn_args->task_handle);
    }
}