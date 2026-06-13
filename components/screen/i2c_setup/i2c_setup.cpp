#include "i2c_setup.hpp"

namespace i2c_setup {
    i2c_master_bus_handle_t i2c_master_bus_init(gpio_num_t sda_pin, gpio_num_t scl_pin) {
        esp_err_t status = ESP_OK;
        i2c_master_bus_config_t i2c_cfg = {
            .i2c_port = I2C_NUM_0,
            .sda_io_num = sda_pin,
            .scl_io_num = scl_pin,
            .clk_source = I2C_CLK_SRC_DEFAULT,
            .glitch_ignore_cnt = 7,
        };
        i2c_master_bus_handle_t i2c_bus = NULL;
        status = i2c_new_master_bus(&i2c_cfg, &i2c_bus);
        ESP_ERROR_CHECK(status);
        return i2c_bus;
    }

    esp_lcd_panel_io_handle_t i2c_lcd_panel_init(i2c_master_bus_handle_t i2c_bus) {
        esp_err_t status = ESP_OK;
        esp_lcd_panel_io_handle_t io_handle = NULL;
        esp_lcd_panel_io_i2c_config_t io_config = {
            .dev_addr = 0x3C,
            .control_phase_bytes = 1,
            .dc_bit_offset = 6,      
            .lcd_cmd_bits = 8,
            .lcd_param_bits = 8,
            .scl_speed_hz = 100000,
        };
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(i2c_bus, &io_config, &io_handle));
        return io_handle;
    }

    esp_lcd_panel_handle_t i2c_lcd_panel_create(esp_lcd_panel_io_handle_t io_handle){
        esp_lcd_panel_handle_t panel_handle = NULL;
        esp_lcd_panel_dev_config_t panel_config = {
            .reset_gpio_num = GPIO_NUM_NC,
            .bits_per_pixel = 1,
        };
        ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(io_handle, &panel_config, &panel_handle));
        return panel_handle;
    }

    lcd_screen_args_t i2c_lcd_panel_init_sequence(gpio_num_t sda_pin, gpio_num_t scl_pin) {
        lcd_screen_args_t screen_args = {0};
        i2c_master_bus_handle_t i2c_bus = i2c_master_bus_init(sda_pin, scl_pin);
        esp_lcd_panel_io_handle_t io_handle = i2c_lcd_panel_init(i2c_bus);
        screen_args.io_handle = io_handle;
        screen_args.panel_handle = i2c_lcd_panel_create(io_handle);
        ESP_LOGI("I2C", "I2C LCD panel initialized successfully");
        return screen_args;
    }
}