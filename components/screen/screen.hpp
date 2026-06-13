#pragma once

#include "driver/gpio.h"
#include "i2c_setup/i2c_setup.hpp"

class screen
{
private:
   gpio_num_t _sda_pin;
   gpio_num_t _scl_pin;
   uint8_t _screen_width;
   uint8_t _screen_height;
public:
    screen(gpio_num_t sda_pin, gpio_num_t scl_pin, uint8_t screen_width, uint8_t screen_height);
    ~screen();
    esp_err_t init();
    
    void show_overview();
    void display_qr_code();
    void display_route_summary();

    uint8_t get_screen_width();
    uint8_t get_screen_height();
};
