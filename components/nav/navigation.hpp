#pragma once

#include "esp_log.h"
#include "task_args.hpp"
#include "iot_button.h"

namespace navigation {
    void button_press_cb(void *button_handle, void *usr_data);
}