#pragma once

#include "driver/gpio.h"
#include "i2c_setup/i2c_setup.hpp"
#include "lvgl_setup/lvgl_setup.hpp"
#include "args/screen_args.hpp"
#include "lvgl_screens/screens.hpp"

enum class screen_state_t {
    OVERVIEW = 0,
    ROUTE_SUMMARY = 1,
    QR_CODE = 2
};

class screen
{
private:
   gpio_num_t _sda_pin;
   gpio_num_t _scl_pin;
   uint8_t _screen_width;
   uint8_t _screen_height;
   screen_state_t _current_screen_state;
public:
    screen(gpio_num_t sda_pin, gpio_num_t scl_pin, uint8_t screen_width, uint8_t screen_height);
    ~screen();
    esp_err_t init();
    void update_overview(route* route_arg);

    void set_state(screen_state_t state, route* route_arg);
    screen_state_t next_state();

    uint8_t get_screen_width();
    uint8_t get_screen_height();
};

