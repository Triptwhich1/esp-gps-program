#include "navigation.hpp"

static uint8_t btn_fsm = 0;

namespace navigation {
    void short_press_cb(void *button_handle, void *usr_data) {
        ESP_LOGI("Navigation", "Short press detected");
        if (usr_data != nullptr) {
            TaskHandle_t navigation_task_handle = static_cast<TaskHandle_t>(usr_data);
            xTaskNotifyGive(navigation_task_handle);
            ESP_LOGI("Navigation", "Notification sent to navigation task");
        } else {
            ESP_LOGE("Navigation", "User data is null in short_press_cb");
        }
        ESP_LOGI("Navigation", "Short press done");
    }
}