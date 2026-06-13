#include "screen.hpp"

screen::screen(gpio_num_t sda_pin, gpio_num_t scl_pin, uint8_t screen_width, uint8_t screen_height)
    : _sda_pin(sda_pin), _scl_pin(scl_pin), _screen_width(screen_width), _screen_height(screen_height) {

    }

screen::~screen() {
}

uint8_t screen::get_screen_width() {
    return _screen_width;
}

uint8_t screen::get_screen_height() {
    return _screen_height;
}

esp_err_t screen::init() {
    lcd_screen_args_t screen_args = i2c_setup::i2c_lcd_panel_init_sequence(_sda_pin, _scl_pin);

    esp_lcd_panel_reset(screen_args.panel_handle);
    esp_lcd_panel_init(screen_args.panel_handle);
    esp_lcd_panel_disp_on_off(screen_args.panel_handle, true);

    lvgl_setup::lvgl_init();
    lvgl_setup::lvgl_port_add_screen(screen_args, _screen_width, _screen_height);

    return ESP_OK;
}

void screen::show_overview() {
    if (lvgl_port_lock(0)) {
        lvgl_screens::draw_overview_screen();
        lvgl_port_unlock();
    }
}

void screen::update_overview(route* route_arg) {
    if (lvgl_port_lock(0)) {
        lvgl_screens::update_overview_screen(route_arg);
        lvgl_port_unlock();
    }
}

void screen::display_route_summary(route* route_arg) {
    if (lvgl_port_lock(0)) {
        lvgl_port_unlock();
    }
}

void screen::display_qr_code() {
    
}

