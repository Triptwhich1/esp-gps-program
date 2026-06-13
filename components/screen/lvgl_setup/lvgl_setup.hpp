#pragma once

#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "args/screen_args.hpp"
#include "esp_log.h"

namespace lvgl_setup {
    void lvgl_init();
    void lvgl_port_add_screen(lcd_screen_args_t screen_args, uint8_t screen_width, uint8_t screen_height);
}