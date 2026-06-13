#pragma once

#include "esp_lcd_io_i2c.h"
#include "driver/i2c_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"
#include "../args/screen_args.hpp"

namespace i2c_setup {
    lcd_screen_args_t i2c_lcd_panel_init_sequence(gpio_num_t sda_pin, gpio_num_t scl_pin);
}