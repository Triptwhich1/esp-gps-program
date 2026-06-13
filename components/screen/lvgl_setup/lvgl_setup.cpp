#include "lvgl_setup.hpp"

namespace lvgl_setup {
    void lvgl_init() {
        const lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();

        esp_err_t err = lvgl_port_init(&lvgl_cfg);
        if (err != ESP_OK) {
            ESP_LOGI("LVGL", "lvgl_port_init failed: %s", esp_err_to_name(err));
        }
    }

    void lvgl_port_add_screen(lcd_screen_args_t screen_args, uint8_t screen_width, uint8_t screen_height) {
        static lv_disp_t * disp_handle;

        const lvgl_port_display_cfg_t disp_cfg = {
            .io_handle = screen_args.io_handle,
            .panel_handle = screen_args.panel_handle,
            .buffer_size = static_cast<uint32_t>(screen_width) * static_cast<uint32_t>(screen_height),
            .double_buffer = false,
            .hres = 128,
            .vres = 64,
            .monochrome = true,
            .color_format = LV_COLOR_FORMAT_I1,
        };
        disp_handle = lvgl_port_add_disp(&disp_cfg);
    }
}