#include "tasks.hpp"

namespace navigation_tasks {
    void navigation_task(void *arg) {
        while (1) {
            ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            ESP_LOGI("Navigation", "Button pressed, starting navigation task");
            // Implement your navigation logic here
        }
    }
}