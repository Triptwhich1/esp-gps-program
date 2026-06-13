idf_component_register(SRCS "screen.cpp" "i2c_setup/i2c_setup.cpp" "lvgl_setup/lvgl_setup.cpp"
                    INCLUDE_DIRS "." "i2c_setup" "lvgl_setup"
                    REQUIRES driver esp_lcd lvgl)

