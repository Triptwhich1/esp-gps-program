#pragma once
#include "esp_lcd_panel_io.h"

struct lcd_screen_args_t {
    esp_lcd_panel_io_handle_t io_handle;
    esp_lcd_panel_handle_t panel_handle;
};