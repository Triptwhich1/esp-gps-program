#pragma once

#include "esp_log.h"
#include "task_args.hpp"

namespace navigation {
    void short_press_cb(void *button_handle, void *usr_data);
    void long_press_cb(void *button_handle, void *usr_data);
}