#include "navigation.hpp"

namespace navigation {
    void short_press_cb(void *button_handle, void *usr_data) {
        ESP_LOGI("BUTTON", "Button pressed");
    }

    void long_press_cb(void *button_handle, void *usr_data);
}