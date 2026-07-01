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

    overview_screen::draw_overview_screen();
    return ESP_OK;
}

void screen::update_overview(route* route_arg) {
    if (lvgl_port_lock(0)) {
        overview_screen::update_overview_screen(route_arg);
        lvgl_port_unlock();
    }
}

void screen::set_state(screen_state_t new_state, route* curr_route)
{
    if (_current_screen_state == new_state) return;

    _current_screen_state = new_state;

    if (lvgl_port_lock(0)) {

        lv_obj_clean(lv_scr_act());  // clear previous screen

        switch (_current_screen_state) {
            case screen_state_t::OVERVIEW:
                overview_screen::draw_overview_screen();
                overview_screen::update_overview_screen(curr_route);
                break;

            case screen_state_t::ROUTE_SUMMARY:
                // route_summary_screen::draw_route_summary_screen();
                ESP_LOGI("Screen", "Route summary screen not implemented yet");
                break;

            case screen_state_t::QR_CODE:
                qr_code_screen::draw_qr_screen();
                break;
        }

        lvgl_port_unlock();
    }
}

screen_state_t screen::next_state() {
    screen_state_t next_state = static_cast<screen_state_t>((static_cast<int>(_current_screen_state) + 1) % 3);
    return next_state;
}